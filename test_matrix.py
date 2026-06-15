from matrix_py import Matrix1

print("Demo: usar matriz de C++ desde Python")

A = Matrix1(2, 2)
B = Matrix1(2, 2)

A[0][0] = 1
A[0][1] = 2
A[1][0] = 3
A[1][1] = 4

B[0][0] = 5
B[0][1] = 6
B[1][0] = 7
B[1][1] = 8

C = A * B

print("\nMatriz A:")
print(A)

print("\nMatriz B:")
print(B)

print("\nResultado C = A * B:")
print(C)

print("\nExtra: usar get y set")
A.set(0, 0, 10)
print("Nuevo valor de A[0][0]:", A.get(0, 0))

print("\nExtra: filas y columnas")
print("Filas de A:", A.rows())
print("Columnas de A:", A.cols())

print("\nDemo de m[3][2] = 8")
M = Matrix1(4, 4)
M[3][2] = 8
print(M)