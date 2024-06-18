#include <iostream>
#include <fstream>
#include <string>

void leerDatosDeArchivoConNumeros(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Crear un objeto ifstream para leer el archivo
    std::string linea;
    int numeroLinea = 1; // Iniciar contador de líneas

    if (archivo.is_open()) {
        while (getline(archivo, linea)) { // Leer líneas del archivo
            std::cout << "Linea " << numeroLinea << ": " << linea << '\n'; // Imprimir número de línea y contenido
            numeroLinea++; // Incrementar el contador de líneas
        }
        archivo.close(); // Cerrar el archivo
    } else {
        std::cout << "No se pudo abrir el archivo\n";
    }
}

int main() {
    leerDatosDeArchivoConNumeros("nosexd.txt"); // Llamar a la función con el nombre del archivo
    return 0;
}
