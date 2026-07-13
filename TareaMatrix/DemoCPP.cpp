#include <iostream>

using namespace std;

/**
 * @brief Suma dos numeros enteros.
 *
 * Esta funcion recibe dos numeros enteros
 * y devuelve el resultado de su suma.
 *
 * @param numero1 Primer numero entero.
 * @param numero2 Segundo numero entero.
 * @return La suma de los dos numeros.
 */
int sumar(int numero1, int numero2) {
    return numero1 + numero2;
}

/**
 * @brief Calcula el promedio de tres notas.
 *
 * Esta funcion recibe tres notas y calcula
 * su promedio aritmetico.
 *
 * @param nota1 Primera nota.
 * @param nota2 Segunda nota.
 * @param nota3 Tercera nota.
 * @return El promedio de las tres notas.
 */
double calcularPromedio(double nota1, double nota2, double nota3) {
    return (nota1 + nota2 + nota3) / 3.0;
}

int main() {
    int numero1;
    int numero2;

    double nota1;
    double nota2;
    double nota3;

    cout << "DEMO DE FUNCIONES DOCUMENTADAS" << endl;

    cout << "\nIngrese el primer numero: ";
    cin >> numero1;

    cout << "Ingrese el segundo numero: ";
    cin >> numero2;

    int resultadoSuma = sumar(numero1, numero2);

    cout << "La suma es: " << resultadoSuma << endl;

    cout << "\nIngrese tres notas:" << endl;

    cout << "Nota 1: ";
    cin >> nota1;

    cout << "Nota 2: ";
    cin >> nota2;

    cout << "Nota 3: ";
    cin >> nota3;

    double promedio = calcularPromedio(nota1, nota2, nota3);

    cout << "El promedio es: " << promedio << endl;

    return 0;
}