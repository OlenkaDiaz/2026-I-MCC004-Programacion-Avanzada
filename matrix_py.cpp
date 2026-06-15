#include <pybind11/pybind11.h>
#include <sstream>
#include "matrix1.h"

namespace py = pybind11;

class Fila {
private:
    Matrix1<int> *matriz;
    size_t fila;

public:
    Fila(Matrix1<int> &m, size_t f) {
        matriz = &m;
        fila = f;
    }

    int get(size_t columna) const {
        return matriz->Get(fila, columna);
    }

    void set(size_t columna, int valor) {
        matriz->Set(fila, columna, valor);
    }
};

PYBIND11_MODULE(matrix_py, m) {
    py::class_<Fila>(m, "Fila")
        .def("__getitem__", &Fila::get)
        .def("__setitem__", &Fila::set);

    py::class_<Matrix1<int>>(m, "Matrix1")
        .def(py::init<size_t, size_t>())

        .def("__getitem__", [](Matrix1<int> &matriz, size_t fila) {
            return Fila(matriz, fila);
        })

        .def("__mul__", [](const Matrix1<int> &a, const Matrix1<int> &b) {
            return a * b;
        })

        .def("get", &Matrix1<int>::Get)
        .def("set", &Matrix1<int>::Set)
        .def("rows", &Matrix1<int>::Rows)
        .def("cols", &Matrix1<int>::Cols)

        .def("__str__", [](Matrix1<int> &matriz) {
            std::ostringstream os;
            os << matriz;
            return os.str();
        });
}