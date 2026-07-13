#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// Protege la escritura en la consola.
mutex bloqueoConsola;

void contarAscendente() {
    for (int i = 1; i <= 5; i++) {

        {
            lock_guard<mutex> bloqueo(bloqueoConsola);
            cout << "Hilo 1: " << i << endl;
        }

        this_thread::sleep_for(
            chrono::milliseconds(500)
        );
    }
}

void contarDescendente() {
    for (int i = 5; i >= 1; i--) {

        {
            lock_guard<mutex> bloqueo(bloqueoConsola);
            cout << "Hilo 2: " << i << endl;
        }

        this_thread::sleep_for(
            chrono::milliseconds(500)
        );
    }
}

int main() {
    cout << "Inicio del programa" << endl;

    thread hilo1(contarAscendente);
    thread hilo2(contarDescendente);

    hilo1.join();
    hilo2.join();

    cout << "Los dos hilos terminaron" << endl;

    return 0;
}