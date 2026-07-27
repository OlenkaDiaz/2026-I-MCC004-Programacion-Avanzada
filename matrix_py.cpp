#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <sstream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <cmath>

#include "matrix1.h"

namespace py = pybind11;

/*
 * Clase auxiliar que representa una fila.
 *
 * Permite utilizar:
 *
 * matriz[fila][columna]
 */
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

    /*
     * Lee un elemento de la fila.
     */
    TDato get(
        TIndice columna
    ) const {
        return matriz->Get(
            fila,
            columna
        );
    }

    /*
     * Modifica un elemento de la fila.
     */
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

/*
 * Convierte una matriz en texto.
 *
 * Permite utilizar:
 *
 * print(matriz)
 */
template <typename TDato>
std::string matrizATexto(
    Matrix1<TDato>& matriz
) {
    std::ostringstream salida;

    salida << matriz;

    return salida.str();
}

/*
 * Extra 1:
 * multiplica una matriz por un escalar.
 *
 * Se implementa aquí para no depender de que
 * matrix1.h tenga operator*(escalar).
 */
template <
    typename TDato,
    typename TIndice
>
Matrix1<TDato> multiplicarPorEscalar(
    Matrix1<TDato>& matriz,
    TDato escalar
) {
    TIndice cantidadFilas =
        static_cast<TIndice>(
            matriz.Rows()
        );

    TIndice cantidadColumnas =
        static_cast<TIndice>(
            matriz.Cols()
        );

    Matrix1<TDato> resultado(
        cantidadFilas,
        cantidadColumnas
    );

    for (
        TIndice fila = TIndice{};
        fila < cantidadFilas;
        ++fila
    ) {
        for (
            TIndice columna = TIndice{};
            columna < cantidadColumnas;
            ++columna
        ) {
            resultado.Set(
                fila,
                columna,
                matriz.Get(
                    fila,
                    columna
                ) * escalar
            );
        }
    }

    return resultado;
}

/*
 * Extra 2:
 * crea la transpuesta de una matriz.
 */
template <
    typename TDato,
    typename TIndice
>
Matrix1<TDato> transponerMatriz(
    Matrix1<TDato>& matriz
) {
    TIndice cantidadFilas =
        static_cast<TIndice>(
            matriz.Rows()
        );

    TIndice cantidadColumnas =
        static_cast<TIndice>(
            matriz.Cols()
        );

    Matrix1<TDato> transpuesta(
        cantidadColumnas,
        cantidadFilas
    );

    for (
        TIndice fila = TIndice{};
        fila < cantidadFilas;
        ++fila
    ) {
        for (
            TIndice columna = TIndice{};
            columna < cantidadColumnas;
            ++columna
        ) {
            transpuesta.Set(
                columna,
                fila,
                matriz.Get(
                    fila,
                    columna
                )
            );
        }
    }

    return transpuesta;
}

/*
 * Extra 3:
 * convierte Matrix1<TDato> en un arreglo NumPy.
 *
 * Los datos se copian desde la matriz de C++
 * hacia un nuevo arreglo de Python.
 */
template <
    typename TDato,
    typename TIndice
>
py::array_t<TDato> matrizANumpy(
    Matrix1<TDato>& matriz
) {
    TIndice cantidadFilas =
        static_cast<TIndice>(
            matriz.Rows()
        );

    TIndice cantidadColumnas =
        static_cast<TIndice>(
            matriz.Cols()
        );

    py::array_t<TDato> arreglo(
        {
            static_cast<py::ssize_t>(
                cantidadFilas
            ),
            static_cast<py::ssize_t>(
                cantidadColumnas
            )
        }
    );

    auto acceso =
        arreglo.template mutable_unchecked<2>();

    for (
        TIndice fila = TIndice{};
        fila < cantidadFilas;
        ++fila
    ) {
        for (
            TIndice columna = TIndice{};
            columna < cantidadColumnas;
            ++columna
        ) {
            acceso(
                static_cast<py::ssize_t>(
                    fila
                ),
                static_cast<py::ssize_t>(
                    columna
                )
            ) = matriz.Get(
                fila,
                columna
            );
        }
    }

    return arreglo;
}

/*
 * Registra Matrix1<TDato> en Python.
 *
 * Esta misma función se utiliza tanto para
 * matrices enteras como para matrices decimales.
 */
template <
    typename TDato,
    typename TIndice
>
void registrarMatriz(
    py::module_& modulo,
    const std::string& nombreFila,
    const std::string& nombreMatriz
) {
    /*
     * Registrar la clase auxiliar Fila.
     */
    py::class_<
        Fila<TDato, TIndice>
    >(
        modulo,
        nombreFila.c_str()
    )
        /*
         * Segundo corchete para leer:
         *
         * valor = matriz[fila][columna]
         */
        .def(
            "__getitem__",
            &Fila<TDato, TIndice>::get
        )

        /*
         * Segundo corchete para modificar:
         *
         * matriz[fila][columna] = valor
         */
        .def(
            "__setitem__",
            &Fila<TDato, TIndice>::set
        );

    /*
     * Registrar Matrix1<TDato>.
     */
    py::class_<
        Matrix1<TDato>
    >(
        modulo,
        nombreMatriz.c_str()
    )
        /*
         * Constructor:
         *
         * matriz = MatrixInt(filas, columnas)
         */
        .def(
            py::init<
                TIndice,
                TIndice
            >()
        )

        /*
         * Primer corchete:
         *
         * matriz[fila]
         *
         * Devuelve un objeto Fila.
         */
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
            },
            py::keep_alive<0, 1>()
        )

        /*
         * Operador de multiplicación.
         *
         * Reconoce dos posibilidades:
         *
         * matrizA * matrizB
         * matrizA * escalar
         */
        .def(
            "__mul__",
            [](
                Matrix1<TDato>& matriz,
                py::object otro
            ) -> Matrix1<TDato> {
                /*
                 * Caso 1:
                 * multiplicación entre matrices.
                 */
                if (
                    py::isinstance<
                        Matrix1<TDato>
                    >(otro)
                ) {
                    Matrix1<TDato>& otraMatriz =
                        otro.cast<
                            Matrix1<TDato>&
                        >();

                    return matriz * otraMatriz;
                }

                /*
                 * Caso 2:
                 * multiplicación por un escalar.
                 */
                try {
                    TDato escalar =
                        otro.cast<TDato>();

                    return multiplicarPorEscalar<
                        TDato,
                        TIndice
                    >(
                        matriz,
                        escalar
                    );
                }
                catch (
                    const py::cast_error&
                ) {
                    throw py::type_error(
                        "La matriz solo puede "
                        "multiplicarse por otra "
                        "matriz o por un numero."
                    );
                }
            },
            py::arg("otro"),
            py::is_operator()
        )

        /*
         * También permite:
         *
         * escalar * matriz
         *
         * Ejemplo:
         *
         * 5 * matriz
         */
        .def(
            "__rmul__",
            [](
                Matrix1<TDato>& matriz,
                TDato escalar
            ) {
                return multiplicarPorEscalar<
                    TDato,
                    TIndice
                >(
                    matriz,
                    escalar
                );
            },
            py::arg("escalar"),
            py::is_operator()
        )

        /*
         * Extra 2:
         *
         * transpuesta = matriz.transpose()
         */
        .def(
            "transpose",
            &transponerMatriz<
                TDato,
                TIndice
            >
        )

        /*
         * Extra 3:
         *
         * arreglo = matriz.to_numpy()
         */
        .def(
            "to_numpy",
            &matrizANumpy<
                TDato,
                TIndice
            >
        )

        /*
         * Métodos auxiliares.
         */
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

        /*
         * Permite utilizar print(matriz).
         */
        .def(
            "__str__",
            &matrizATexto<TDato>
        )

        .def(
            "__repr__",
            &matrizATexto<TDato>
        );
}

/*
 * Creación del módulo de Python.
 */
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

    /*
     * Matrices de enteros.
     */
    registrarMatriz<
        TipoEntero,
        TipoIndice
    >(
        modulo,
        "FilaInt",
        "MatrixInt"
    );

    /*
     * Matrices de decimales.
     */
    registrarMatriz<
        TipoDecimal,
        TipoIndice
    >(
        modulo,
        "FilaFloat",
        "MatrixFloat"
    );
}