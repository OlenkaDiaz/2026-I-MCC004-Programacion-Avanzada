import numpy as np

from matrix_py import MatrixInt, MatrixFloat

print("Demo: usar una matriz de C++ desde Python")

# ==================================================
# MATRICES DE ENTEROS
# ==================================================

print("\n=== MATRICES DE ENTEROS ===")

A = MatrixInt(2, 2)
B = MatrixInt(2, 2)

# Valores de la matriz A.
A[0][0] = 1
A[0][1] = 2
A[1][0] = 3
A[1][1] = 4

# Valores de la matriz B.
B[0][0] = 5
B[0][1] = 6
B[1][0] = 7
B[1][1] = 8

# Requisito: imprimir matrices.
print("\nMatriz A:")
print(A)

print("\nMatriz B:")
print(B)

# Requisito: multiplicación entre matrices.
C = A * B

print("\nResultado C = A * B:")
print(C)

assert C.get(0, 0) == 19
assert C.get(0, 1) == 22
assert C.get(1, 0) == 43
assert C.get(1, 1) == 50

# ==================================================
# REQUISITO: DOBLE CORCHETE
# ==================================================

print("\n=== REQUISITO: M[3][2] = 8 ===")

M = MatrixInt(4, 4)

M[3][2] = 8

print(M)

print(
    "Valor leído de M[3][2]:",
    M[3][2]
)

assert M[3][2] == 8

# ==================================================
# EXTRA 1: MULTIPLICACIÓN POR ESCALAR
# ==================================================

print(
    "\n=== EXTRA 1: "
    "MULTIPLICACIÓN POR ESCALAR ==="
)

D = A * 5

print("\nResultado D = A * 5:")
print(D)

assert D.get(0, 0) == 5
assert D.get(0, 1) == 10
assert D.get(1, 0) == 15
assert D.get(1, 1) == 20

# También funciona con el escalar a la izquierda.
E = 5 * A

print("\nResultado E = 5 * A:")
print(E)

assert E.get(0, 0) == 5
assert E.get(0, 1) == 10
assert E.get(1, 0) == 15
assert E.get(1, 1) == 20

# ==================================================
# EXTRA 2: TRANSPUESTA
# ==================================================

print("\n=== EXTRA 2: TRANSPUESTA ===")

AT = A.transpose()

print("\nMatriz A:")
print(A)

print("\nTranspuesta de A:")
print(AT)

assert AT.get(0, 0) == 1
assert AT.get(0, 1) == 3
assert AT.get(1, 0) == 2
assert AT.get(1, 1) == 4

# ==================================================
# EXTRA 3: CONVERSIÓN A NUMPY
# ==================================================

print("\n=== EXTRA 3: CONVERSIÓN A NUMPY ===")

arreglo_A = A.to_numpy()

print("\nMatriz A convertida a NumPy:")
print(arreglo_A)

print(
    "Tipo del resultado:",
    type(arreglo_A)
)

print(
    "Dimensiones:",
    arreglo_A.shape
)

print(
    "Suma de elementos con NumPy:",
    np.sum(arreglo_A)
)

assert isinstance(
    arreglo_A,
    np.ndarray
)

assert arreglo_A.shape == (2, 2)

assert np.array_equal(
    arreglo_A,
    np.array(
        [
            [1, 2],
            [3, 4]
        ]
    )
)

# ==================================================
# MÉTODOS AUXILIARES
# ==================================================

print("\n=== MÉTODOS AUXILIARES ===")

print("\nUsar get y set")

A.set(0, 0, 10)

print(
    "Nuevo valor de A[0][0]:",
    A.get(0, 0)
)

assert A.get(0, 0) == 10

print("\nConsultar filas y columnas")

print(
    "Filas de A:",
    A.rows()
)

print(
    "Columnas de A:",
    A.cols()
)

assert A.rows() == 2
assert A.cols() == 2

# ==================================================
# MATRICES DECIMALES
# ==================================================

print("\n=== MATRICES DE DECIMALES ===")

F = MatrixFloat(2, 2)
G = MatrixFloat(2, 2)

F[0][0] = 1.5
F[0][1] = 2.5
F[1][0] = 3.5
F[1][1] = 4.5

G[0][0] = 1.0
G[0][1] = 2.0
G[1][0] = 3.0
G[1][1] = 4.0

print("\nMatriz F:")
print(F)

print("\nMatriz G:")
print(G)

H = F * G

print("\nResultado H = F * G:")
print(H)

assert np.isclose(
    H.get(0, 0),
    9.0
)

assert np.isclose(
    H.get(0, 1),
    13.0
)

assert np.isclose(
    H.get(1, 0),
    17.0
)

assert np.isclose(
    H.get(1, 1),
    25.0
)

# ==================================================
# EXTRAS CON MATRICES DECIMALES
# ==================================================

print(
    "\nMultiplicación de matriz "
    "decimal por escalar"
)

J = F * 2.0

print("\nResultado J = F * 2.0:")
print(J)

assert np.isclose(
    J.get(0, 0),
    3.0
)

assert np.isclose(
    J.get(0, 1),
    5.0
)

assert np.isclose(
    J.get(1, 0),
    7.0
)

assert np.isclose(
    J.get(1, 1),
    9.0
)

print("\nTranspuesta de F:")

FT = F.transpose()

print(FT)

assert np.isclose(
    FT.get(0, 1),
    3.5
)

assert np.isclose(
    FT.get(1, 0),
    2.5
)

print("\nF convertida a NumPy:")

arreglo_F = F.to_numpy()

print(arreglo_F)

assert np.allclose(
    arreglo_F,
    np.array(
        [
            [1.5, 2.5],
            [3.5, 4.5]
        ]
    )
)

print(
    "\nTodas las pruebas "
    "finalizaron correctamente."
)