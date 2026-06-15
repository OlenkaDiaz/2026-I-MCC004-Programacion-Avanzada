from matrix_py import Matrix1

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

print("Matriz A:")
print(A)

print("Matriz B:")
print(B)

print("Resultado C = A * B:")
print(C)