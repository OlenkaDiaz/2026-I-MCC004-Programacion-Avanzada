from matrix_py import MatrixInt, MatrixFloat

print("Demo: usar matriz de C++ desde Python")
# ==================================================
# PRUEBA CON MatrixInt
# ==================================================
print("\n=== MATRICES DE ENTEROS ===")
A = MatrixInt(2, 2)
B = MatrixInt(2, 2)

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
M = MatrixInt(4, 4)
M[3][2] = 8
print(M)

# ==================================================
# PRUEBA CON Matrixfloat
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

H = F * G

print("\nMatriz F:")
print(F)

print("\nMatriz G:")
print(G)

print("\nResultado H = F * G:")
print(H)

print("\nPrueba get y set con float")
F.set(0, 0, 7.25)
print("Nuevo valor de F[0][0]:", F.get(0, 0))

print("\nFilas y columnas de F")
print("Filas de F:", F.rows())
print("Columnas de F:", F.cols())