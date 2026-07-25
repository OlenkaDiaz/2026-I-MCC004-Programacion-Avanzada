#include <pybind11/pybind11.h>
#include <sstream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include "matrix1.h"

namespace py = pybind11;

template <
    typename TDato,
    typename TIndice
>
class Fila {
private:
    Matrix1<TDato>* matriz;
    TIndice fila;

public:
    Fila(
        Matrix1<TDato>& matrizRecibida,
        TIndice filaRecibida
    )
        : matriz(&matrizRecibida),
          fila(filaRecibida) {
    }

    TDato get(
        TIndice columna
    ) const {
        return matriz->Get(
            fila,
            columna
        );
    }

    void set(
        TIndice columna,
        TDato valor
    ) {
        matriz->Set(
            fila,
            columna,
            valor
        );
    }
};

template <typename TDato>
std::string matrizATexto(
    Matrix1<TDato>& matriz
) {
    std::ostringstream salida;

    salida << matriz;

    return salida.str();
}

template <
    typename TDato,
    typename TIndice
>
void registrarMatriz(
    py::module_& modulo,
    const std::string& nombreFila,
    const std::string& nombreMatriz
) {
    py::class_<
        Fila<TDato, TIndice>
    >(
        modulo,
        nombreFila.c_str()
    )
        .def(
            "__getitem__",
            &Fila<TDato, TIndice>::get
        )
        .def(
            "__setitem__",
            &Fila<TDato, TIndice>::set
        );

    py::class_<
        Matrix1<TDato>
    >(
        modulo,
        nombreMatriz.c_str()
    )
        .def(
            py::init<
                TIndice,
                TIndice
            >()
        )

        .def(
            "__getitem__",
            [](
                Matrix1<TDato>& matriz,
                TIndice fila
            ) {
                return Fila<
                    TDato,
                    TIndice
                >(
                    matriz,
                    fila
                );
            }
        )

        .def(
            "__mul__",
            [](
                const Matrix1<TDato>& matrizA,
                const Matrix1<TDato>& matrizB
            ) {
                return matrizA * matrizB;
            }
        )

        .def(
            "get",
            &Matrix1<TDato>::Get
        )

        .def(
            "set",
            &Matrix1<TDato>::Set
        )

        .def(
            "rows",
            &Matrix1<TDato>::Rows
        )

        .def(
            "cols",
            &Matrix1<TDato>::Cols
        )

        .def(
            "__str__",
            &matrizATexto<TDato>
        )

        .def(
            "__repr__",
            &matrizATexto<TDato>
        );
}

PYBIND11_MODULE(
    matrix_py,
    modulo
) {
    using TipoEntero =
        std::int32_t;

    using TipoDecimal =
        std::float_t;

    using TipoIndice =
        std::size_t;

    registrarMatriz<
        TipoEntero,
        TipoIndice
    >(
        modulo,
        "FilaInt",
        "MatrixInt"
    );

    registrarMatriz<
        TipoDecimal,
        TipoIndice
    >(
        modulo,
        "FilaFloat",
        "MatrixFloat"
    );
}