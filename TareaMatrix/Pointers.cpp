#include <iostream>
#include <sstream>
#include "Pointers.h"
#include "matrix1.h"

using namespace std;

template <typename T>
void SumarValor(T &n, T valor)
{
    n = n + valor;
}

void DemoPointersMatrix()
{
    cout << "\nDemo de matriz con doble puntero\n";

    Matrix1<int> matriz;

    istringstream datos("2 3 5 6 7 8 9 10");

    datos >> matriz;

    cout << "\nMatriz inicial:\n";
    cout << matriz;

    matriz.ApplyFunctionToAll(SumarValor<int>, 3);

    cout << "\nMatriz despues de sumar 3:\n";
    cout << matriz;
}