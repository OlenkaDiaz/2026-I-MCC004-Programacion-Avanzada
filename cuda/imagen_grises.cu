
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstddef>
#include <cuda_runtime.h>

using namespace std;

// Cada hilo transforma un pixel de color a escala de grises.
template <
    typename TPixel,
    typename TCalculo
>
__global__ void convertirAGris(
    const TPixel* imagenColor,
    TPixel* imagenGris,
    size_t ancho,
    size_t alto
) {
    size_t x =
        static_cast<size_t>(blockIdx.x) *
        static_cast<size_t>(blockDim.x) +
        static_cast<size_t>(threadIdx.x);

    size_t y =
        static_cast<size_t>(blockIdx.y) *
        static_cast<size_t>(blockDim.y) +
        static_cast<size_t>(threadIdx.y);

    if (x < ancho && y < alto) {
        size_t posicion =
            y * ancho + x;

        size_t indiceColor =
            posicion * 3;

        TPixel rojo =
            imagenColor[indiceColor];

        TPixel verde =
            imagenColor[indiceColor + 1];

        TPixel azul =
            imagenColor[indiceColor + 2];

        TCalculo nivelGris =
            static_cast<TCalculo>(0.299) *
            static_cast<TCalculo>(rojo)
            +
            static_cast<TCalculo>(0.587) *
            static_cast<TCalculo>(verde)
            +
            static_cast<TCalculo>(0.114) *
            static_cast<TCalculo>(azul);

        imagenGris[posicion] =
            static_cast<TPixel>(nivelGris);
    }
}

// Guarda una imagen a color.
template <typename TPixel>
void guardarPPM(
    const string& nombre,
    const vector<TPixel>& imagen,
    size_t ancho,
    size_t alto
) {
    ofstream archivo(
        nombre,
        ios::binary
    );

    archivo << "P6\n";
    archivo
        << ancho
        << " "
        << alto
        << "\n";

    archivo << "255\n";

    archivo.write(
        reinterpret_cast<const char*>(
            imagen.data()
        ),
        static_cast<streamsize>(
            imagen.size() *
            sizeof(TPixel)
        )
    );
}

// Guarda una imagen en escala de grises.
template <typename TPixel>
void guardarPGM(
    const string& nombre,
    const vector<TPixel>& imagen,
    size_t ancho,
    size_t alto
) {
    ofstream archivo(
        nombre,
        ios::binary
    );

    archivo << "P5\n";
    archivo
        << ancho
        << " "
        << alto
        << "\n";

    archivo << "255\n";

    archivo.write(
        reinterpret_cast<const char*>(
            imagen.data()
        ),
        static_cast<streamsize>(
            imagen.size() *
            sizeof(TPixel)
        )
    );
}

// Ejecuta todo el procesamiento usando plantillas.
template <
    typename TPixel,
    typename TCalculo
>
void ejecutarConversionImagen() {
    const size_t ancho = 512;
    const size_t alto = 512;

    const size_t cantidadPixeles =
        ancho * alto;

    vector<TPixel> imagenColor(
        cantidadPixeles * 3
    );

    vector<TPixel> imagenGris(
        cantidadPixeles
    );

    // Crear una imagen de colores.
    for (
        size_t y = 0;
        y < alto;
        y++
    ) {
        for (
            size_t x = 0;
            x < ancho;
            x++
        ) {
            size_t posicion =
                y * ancho + x;

            size_t indice =
                posicion * 3;

            imagenColor[indice] =
                static_cast<TPixel>(
                    x * 255 / ancho
                );

            imagenColor[indice + 1] =
                static_cast<TPixel>(
                    y * 255 / alto
                );

            imagenColor[indice + 2] =
                static_cast<TPixel>(150);
        }
    }

    TPixel* gpuColor;
    TPixel* gpuGris;

    size_t tamanioColor =
        cantidadPixeles *
        3 *
        sizeof(TPixel);

    size_t tamanioGris =
        cantidadPixeles *
        sizeof(TPixel);

    cudaMalloc(
        reinterpret_cast<void**>(&gpuColor),
        tamanioColor
    );

    cudaMalloc(
        reinterpret_cast<void**>(&gpuGris),
        tamanioGris
    );

    cudaMemcpy(
        gpuColor,
        imagenColor.data(),
        tamanioColor,
        cudaMemcpyHostToDevice
    );

    dim3 hilosPorBloque(16, 16);

    dim3 cantidadBloques(
        static_cast<unsigned int>(
            (
                ancho +
                hilosPorBloque.x -
                1
            ) / hilosPorBloque.x
        ),

        static_cast<unsigned int>(
            (
                alto +
                hilosPorBloque.y -
                1
            ) / hilosPorBloque.y
        )
    );

    convertirAGris<
        TPixel,
        TCalculo
    >
    <<<cantidadBloques, hilosPorBloque>>>(
        gpuColor,
        gpuGris,
        ancho,
        alto
    );

    cudaDeviceSynchronize();

    cudaMemcpy(
        imagenGris.data(),
        gpuGris,
        tamanioGris,
        cudaMemcpyDeviceToHost
    );

    guardarPPM<TPixel>(
        "imagen_color.ppm",
        imagenColor,
        ancho,
        alto
    );

    guardarPGM<TPixel>(
        "imagen_gris.pgm",
        imagenGris,
        ancho,
        alto
    );

    cudaFree(gpuColor);
    cudaFree(gpuGris);

    cout
        << "Imagen procesada correctamente con CUDA."
        << endl;

    cout
        << "Se crearon imagen_color.ppm "
        << "e imagen_gris.pgm."
        << endl;
}

int main() {
    // Tipos concretos que reemplazarán a las plantillas.
    using TipoPixel = unsigned char;
    using TipoCalculo = float;

    ejecutarConversionImagen<
        TipoPixel,
        TipoCalculo
    >();

    return 0;
}
