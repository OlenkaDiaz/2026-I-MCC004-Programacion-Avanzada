#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

/**
 * @brief Almacena el estado físico del cuerpo en un instante.
 *
 * Guarda el tiempo, la posición, la velocidad, la aceleración
 * y las diferentes formas de energía calculadas durante la
 * simulación de caída libre.
 */
struct EstadoMovimiento {
    double tiempo;
    double posicion;
    double velocidad;
    double aceleracion;
    double energiaCinetica;
    double energiaPotencial;
    double energiaMecanica;
};

/**
 * @brief Simula la caída libre mediante el método de Euler semiimplícito.
 *
 * La función calcula de manera aproximada la evolución temporal
 * de un cuerpo sometido únicamente a la acción de la gravedad.
 *
 * En cada paso se actualiza primero la velocidad y después la
 * posición:
 *
 * velocidad = velocidad - gravedad * pasoTiempo
 *
 * posicion = posicion + velocidad * pasoTiempo
 *
 * La simulación termina cuando el cuerpo llega al suelo.
 *
 * @param alturaInicial Altura inicial expresada en metros.
 * @param velocidadInicial Velocidad inicial en metros por segundo.
 * Una velocidad positiva representa movimiento hacia arriba.
 * @param pasoTiempo Intervalo entre cálculos consecutivos.
 * @param gravedad Magnitud de la aceleración gravitatoria.
 * @param masa Masa del cuerpo expresada en kilogramos.
 *
 * @return Vector con todos los estados calculados durante la caída.
 *
 * @throws invalid_argument Si la altura, el paso de tiempo,
 * la gravedad o la masa no son valores válidos.
 * @throws runtime_error Si la simulación supera el máximo
 * permitido de iteraciones.
 *
 * @note Al disminuir el paso de tiempo se obtiene normalmente
 * una aproximación más precisa, pero se realizan más cálculos.
 */
vector<EstadoMovimiento> simularCaidaLibre(
    double alturaInicial,
    double velocidadInicial,
    double pasoTiempo,
    double gravedad,
    double masa
) {
    if (alturaInicial <= 0.0) {
        throw invalid_argument(
            "La altura inicial debe ser mayor que cero."
        );
    }

    if (pasoTiempo <= 0.0) {
        throw invalid_argument(
            "El paso de tiempo debe ser mayor que cero."
        );
    }

    if (gravedad <= 0.0) {
        throw invalid_argument(
            "La gravedad debe ser mayor que cero."
        );
    }

    if (masa <= 0.0) {
        throw invalid_argument(
            "La masa debe ser mayor que cero."
        );
    }

    vector<EstadoMovimiento> estados;

    double tiempo = 0.0;
    double posicion = alturaInicial;
    double velocidad = velocidadInicial;

    const size_t maximoPasos = 1000000;

    for (size_t paso = 0; paso < maximoPasos; paso++) {

        double energiaCinetica =
            0.5 * masa * velocidad * velocidad;

        double energiaPotencial =
            masa * gravedad * posicion;

        double energiaMecanica =
            energiaCinetica + energiaPotencial;

        EstadoMovimiento estado;

        estado.tiempo = tiempo;
        estado.posicion = posicion;
        estado.velocidad = velocidad;
        estado.aceleracion = -gravedad;
        estado.energiaCinetica = energiaCinetica;
        estado.energiaPotencial = energiaPotencial;
        estado.energiaMecanica = energiaMecanica;

        estados.push_back(estado);

        if (posicion <= 0.0 && tiempo > 0.0) {
            return estados;
        }

        // Método de Euler semiimplícito:
        // primero se actualiza la velocidad.
        velocidad = velocidad - gravedad * pasoTiempo;

        // Después se actualiza la posición.
        posicion = posicion + velocidad * pasoTiempo;

        tiempo = tiempo + pasoTiempo;

        // Evita mostrar alturas negativas.
        if (posicion < 0.0) {
            posicion = 0.0;
        }
    }

    throw runtime_error(
        "La simulacion supero el maximo de iteraciones."
    );
}

/**
 * @brief Calcula analíticamente el tiempo de impacto.
 *
 * La función resuelve la ecuación de posición:
 *
 * alturaInicial + velocidadInicial * t
 * - 0.5 * gravedad * t^2 = 0
 *
 * Se selecciona la solución positiva porque representa
 * un instante posterior al inicio del movimiento.
 *
 * @param alturaInicial Altura inicial expresada en metros.
 * @param velocidadInicial Velocidad inicial en metros por segundo.
 * @param gravedad Magnitud de la aceleración gravitatoria.
 *
 * @return Tiempo exacto de impacto expresado en segundos.
 *
 * @throws invalid_argument Si la altura o la gravedad
 * no tienen valores válidos.
 */
template <typename T>
T calcularTiempoImpacto(
    T alturaInicial,
    T velocidadInicial,
    T gravedad
) {
    if (alturaInicial <= 0.0) {
        throw invalid_argument(
            "La altura inicial debe ser mayor que cero."
        );
    }

    if (gravedad <= 0.0) {
        throw invalid_argument(
            "La gravedad debe ser mayor que cero."
        );
    }

    double discriminante =
        velocidadInicial * velocidadInicial
        + 2.0 * gravedad * alturaInicial;

    double tiempoImpacto =
        (
            velocidadInicial
            + sqrt(discriminante)
        ) / gravedad;

    return tiempoImpacto;
}

/**
 * @brief Calcula el error absoluto entre dos resultados.
 *
 * @param valorAnalitico Resultado obtenido mediante
 * la ecuación exacta.
 * @param valorNumerico Resultado obtenido mediante
 * la simulación numérica.
 *
 * @return Diferencia absoluta entre ambos valores.
 */
double calcularErrorAbsoluto(
    double valorAnalitico,
    double valorNumerico
) {
    return abs(valorAnalitico - valorNumerico);
}

/**
 * @brief Calcula el error relativo porcentual.
 *
 * @param valorAnalitico Valor considerado como referencia.
 * @param valorNumerico Valor obtenido mediante aproximación.
 *
 * @return Error relativo expresado como porcentaje.
 *
 * @throws invalid_argument Si el valor analítico es igual a cero.
 */
double calcularErrorRelativo(
    double valorAnalitico,
    double valorNumerico
) {
    if (valorAnalitico == 0.0) {
        throw invalid_argument(
            "No se puede calcular error relativo respecto de cero."
        );
    }

    return (
        abs(valorAnalitico - valorNumerico)
        / abs(valorAnalitico)
    ) * 100.0;
}

/**
 * @brief Guarda los resultados en un archivo CSV.
 *
 * El archivo generado puede abrirse con Excel para realizar
 * tablas y gráficos de posición, velocidad y energía.
 *
 * @param estados Vector con los resultados de la simulación.
 * @param nombreArchivo Nombre del archivo que será generado.
 *
 * @throws runtime_error Si no es posible crear el archivo.
 */
void guardarResultadosCSV(
    const vector<EstadoMovimiento>& estados,
    const string& nombreArchivo
) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw runtime_error(
            "No se pudo crear el archivo CSV."
        );
    }

    archivo
        << "Tiempo,"
        << "Posicion,"
        << "Velocidad,"
        << "Aceleracion,"
        << "EnergiaCinetica,"
        << "EnergiaPotencial,"
        << "EnergiaMecanica\n";

    for (const EstadoMovimiento& estado : estados) {
        archivo
            << estado.tiempo << ","
            << estado.posicion << ","
            << estado.velocidad << ","
            << estado.aceleracion << ","
            << estado.energiaCinetica << ","
            << estado.energiaPotencial << ","
            << estado.energiaMecanica << "\n";
    }

    archivo.close();
}

int main() {
    try {
        double alturaInicial;
        double velocidadInicial;
        double pasoTiempo;
        double gravedad;
        double masa;

        cout << "=========================================\n";
        cout << " SIMULACION NUMERICA DE CAIDA LIBRE\n";
        cout << "=========================================\n";

        cout << "\nIngrese la altura inicial en metros: ";
        cin >> alturaInicial;

        cout << "Ingrese la velocidad inicial en m/s: ";
        cin >> velocidadInicial;

        cout << "Ingrese el paso de tiempo en segundos: ";
        cin >> pasoTiempo;

        cout << "Ingrese la gravedad en m/s^2: ";
        cin >> gravedad;

        cout << "Ingrese la masa del cuerpo en kg: ";
        cin >> masa;

        vector<EstadoMovimiento> resultados =
            simularCaidaLibre(
                alturaInicial,
                velocidadInicial,
                pasoTiempo,
                gravedad,
                masa
            );

        cout << fixed << setprecision(4);

        cout << "\nRESULTADOS DE LA SIMULACION\n\n";

        cout
            << left
            << setw(10) << "Tiempo"
            << setw(14) << "Posicion"
            << setw(14) << "Velocidad"
            << setw(14) << "Acelerac."
            << setw(16) << "E. cinetica"
            << setw(16) << "E. potencial"
            << setw(16) << "E. mecanica"
            << endl;

        cout << string(100, '-') << endl;

        for (const EstadoMovimiento& estado : resultados) {
            cout
                << left
                << setw(10) << estado.tiempo
                << setw(14) << estado.posicion
                << setw(14) << estado.velocidad
                << setw(14) << estado.aceleracion
                << setw(16) << estado.energiaCinetica
                << setw(16) << estado.energiaPotencial
                << setw(16) << estado.energiaMecanica
                << endl;
        }

        double tiempoAnalitico =
            calcularTiempoImpacto(
                alturaInicial,
                velocidadInicial,
                gravedad
            );

        double tiempoNumerico =
            resultados.back().tiempo;

        double errorAbsoluto =
            calcularErrorAbsoluto(
                tiempoAnalitico,
                tiempoNumerico
            );

        double errorRelativo =
            calcularErrorRelativo(
                tiempoAnalitico,
                tiempoNumerico
            );

        cout << "\nCOMPARACION DE RESULTADOS\n";
        cout << "Tiempo analitico: "
             << tiempoAnalitico
             << " segundos\n";

        cout << "Tiempo numerico:  "
             << tiempoNumerico
             << " segundos\n";

        cout << "Error absoluto:   "
             << errorAbsoluto
             << " segundos\n";

        cout << "Error relativo:   "
             << errorRelativo
             << " %\n";

        guardarResultadosCSV(
            resultados,
            "resultados_caida_libre.csv"
        );

        cout << "\nLos resultados fueron guardados en:\n";
        cout << "resultados_caida_libre.csv\n";

        cout << "\nEl archivo puede abrirse con Excel "
             << "para realizar graficos.\n";
    }
    catch (const exception& error) {
        cerr << "\nError: "
             << error.what()
             << endl;

        return 1;
    }

    return 0;
}