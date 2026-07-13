 #include <iostream>
#include <fstream>
#include <vector>
#include <cuda_runtime.h>

using namespace std;

// Cada hilo transforma un pixel de color a escala de grises.
__global__ void convertirAGris(
    const unsigned char* imagenColor,
    unsigned char* imagenGris,
    int ancho,
    int alto
) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < ancho && y < alto) {
        int posicion = y * ancho + x;
        int indiceColor = posicion * 3;

        unsigned char rojo = imagenColor[indiceColor];
        unsigned char verde = imagenColor[indiceColor + 1];
        unsigned char azul = imagenColor[indiceColor + 2];

        imagenGris[posicion] = static_cast<unsigned char>(
            0.299f * rojo +
            0.587f * verde +
            0.114f * azul
        );
    }
}

// Guarda una imagen a color.
void guardarPPM(
    const string& nombre,
    const vector<unsigned char>& imagen,
    int ancho,
    int alto
) {
    ofstream archivo(nombre, ios::binary);

    archivo << "P6\n";
    archivo << ancho << " " << alto << "\n";
    archivo << "255\n";

    archivo.write(
        reinterpret_cast<const char*>(imagen.data()),
        imagen.size()
    );
}

// Guarda una imagen en escala de grises.
void guardarPGM(
    const string& nombre,
    const vector<unsigned char>& imagen,
    int ancho,
    int alto
) {
    ofstream archivo(nombre, ios::binary);

    archivo << "P5\n";
    archivo << ancho << " " << alto << "\n";
    archivo << "255\n";

    archivo.write(
        reinterpret_cast<const char*>(imagen.data()),
        imagen.size()
    );
}

int main() {
    const int ancho = 512;
    const int alto = 512;
    const int cantidadPixeles = ancho * alto;

    vector<unsigned char> imagenColor(cantidadPixeles * 3);
    vector<unsigned char> imagenGris(cantidadPixeles);

    // Crear una imagen de colores para la demostracion.
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            int posicion = y * ancho + x;
            int indice = posicion * 3;

            imagenColor[indice] =
                static_cast<unsigned char>(x * 255 / ancho);

            imagenColor[indice + 1] =
                static_cast<unsigned char>(y * 255 / alto);

            imagenColor[indice + 2] = 150;
        }
    }

    unsigned char* gpuColor;
    unsigned char* gpuGris;

    cudaMalloc(
        reinterpret_cast<void**>(&gpuColor),
        cantidadPixeles * 3 * sizeof(unsigned char)
    );

    cudaMalloc(
        reinterpret_cast<void**>(&gpuGris),
        cantidadPixeles * sizeof(unsigned char)
    );

    cudaMemcpy(
        gpuColor,
        imagenColor.data(),
        cantidadPixeles * 3 * sizeof(unsigned char),
        cudaMemcpyHostToDevice
    );

    dim3 hilosPorBloque(16, 16);

    dim3 cantidadBloques(
        (ancho + hilosPorBloque.x - 1) / hilosPorBloque.x,
        (alto + hilosPorBloque.y - 1) / hilosPorBloque.y
    );

    convertirAGris<<<cantidadBloques, hilosPorBloque>>>(
        gpuColor,
        gpuGris,
        ancho,
        alto
    );

    cudaDeviceSynchronize();

    cudaMemcpy(
        imagenGris.data(),
        gpuGris,
        cantidadPixeles * sizeof(unsigned char),
        cudaMemcpyDeviceToHost
    );

    guardarPPM(
        "imagen_color.ppm",
        imagenColor,
        ancho,
        alto
    );

    guardarPGM(
        "imagen_gris.pgm",
        imagenGris,
        ancho,
        alto
    );

    cudaFree(gpuColor);
    cudaFree(gpuGris);

    cout << "Imagen procesada correctamente con CUDA." << endl;
    cout << "Se crearon imagen_color.ppm e imagen_gris.pgm." << endl;

    return 0;
}