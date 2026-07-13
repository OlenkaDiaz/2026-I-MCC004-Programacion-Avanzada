#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    string correo;

    cout << "Ingrese un correo electronico: ";
    getline(cin, correo);

    regex patronCorreo(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
    );

    if (regex_match(correo, patronCorreo)) {
        cout << "El correo tiene un formato valido." << endl;
    } else {
        cout << "El correo no tiene un formato valido." << endl;
    }

    string texto;

    cout << "\nIngrese un texto que contenga numeros: ";
    getline(cin, texto);

    regex patronNumero("[0-9]+");

    sregex_iterator inicio(
        texto.begin(),
        texto.end(),
        patronNumero
    );

    sregex_iterator fin;

    cout << "Numeros encontrados:" << endl;

    for (sregex_iterator it = inicio; it != fin; ++it) {
        cout << it->str() << endl;
    }

    return 0;
}