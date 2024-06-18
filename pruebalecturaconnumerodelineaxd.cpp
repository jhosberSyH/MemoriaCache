#include <iostream>
#include <fstream>
#include <string>

void leerDatosDeArchivoConNumeros(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Crear un objeto ifstream para leer el archivo
    std::string linea;
    int numeroLinea = 1; // Iniciar contador de l�neas

    if (archivo.is_open()) {
        while (getline(archivo, linea)) { // Leer l�neas del archivo
            std::cout << "Linea " << numeroLinea << ": " << linea << '\n'; // Imprimir n�mero de l�nea y contenido
            numeroLinea++; // Incrementar el contador de l�neas
        }
        archivo.close(); // Cerrar el archivo
    } else {
        std::cout << "No se pudo abrir el archivo\n";
    }
}

int main() {
    leerDatosDeArchivoConNumeros("nosexd.txt"); // Llamar a la funci�n con el nombre del archivo
    return 0;
}
