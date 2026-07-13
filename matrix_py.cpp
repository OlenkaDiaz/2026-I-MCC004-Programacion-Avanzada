#include <pybind11/pybind11.h>
#include <sstream>
#include "matrix1.h"

namespace py = pybind11;

template <typename T>
class Fila {
    private:
        Matrix1<T> *matriz;
        size_t fila;
    public:
        Fila(Matrix1<T> &m, size_t f){
            matriz= &m;
            fila=f;
        }
        T get(size_t columna) const {
            return matriz->Get(fila, columna);
        }
        void set(size_t columna, T valor){
            matriz->Set(fila, columna, valor);
        }
};

PYBIND11_MODULE(matrix_py, m) {
    // Fila para matrices de números enteros
    py::class_<Fila<int>>(m, "FilaInt")
        .def("__getitem__", &Fila<int>::get)
        .def("__setitem__", &Fila<int>::set);
    // Fila para matrices de números decimales
    py::class_<Fila<float>>(m, "FilaFloat")
        .def("__getitem__", &Fila<float>::get)
        .def("__setitem__", &Fila<float>::set);
    // Matrix1<int> se llamará Matrix1 en Python
    py::class_<Matrix1<int>>(m, "Matrix1")
        .def(py::init<size_t, size_t>())

        .def("__getitem__", [](Matrix1<int> &matriz, size_t fila) {
            return Fila<int>(matriz, fila);
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

        // Matrix1<float> se llamará MatrixFloat en Python
    py::class_<Matrix1<float>>(m, "MatrixFloat")
        .def(py::init<size_t, size_t>())

        .def("__getitem__", [](Matrix1<float> &matriz, size_t fila) {
            return Fila<float>(matriz, fila);
        })

        .def("__mul__", [](const Matrix1<float> &a,
            const Matrix1<float> &b) {
            return a * b;
        })
        .def("get", &Matrix1<float>::Get)
        .def("set", &Matrix1<float>::Set)
        .def("rows", &Matrix1<float>::Rows)
        .def("cols", &Matrix1<float>::Cols)

        .def("__str__", [](Matrix1<float> &matriz) {
            std::ostringstream os;
            os << matriz;
            return os.str();
        })

        .def("__repr__", [](Matrix1<float> &matriz) {
            std::ostringstream os;
            os << matriz;
            return os.str();
        });
}