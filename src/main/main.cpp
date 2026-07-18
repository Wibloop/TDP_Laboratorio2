#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../Grafo/Grafo.h"
#include "../Camino/Camino.h"

// Funcion que parsea el archivo de texto y construye el Grafo con los datos contenidos en el archivo de texto
std::unique_ptr<Grafo> cargarGrafo(const std::string& rutaArchivo){
    // Instanciamos el flujo de lectura
    std::ifstream archivo(rutaArchivo);
    
    // Validacion de apertura correcta
    if (!archivo.is_open()){
        std::cerr << "Error: No se pudo abrir el archivo de configuracion en la ruta especificada\n";
        return nullptr;
    }

    int n, m, W;
    // Lectura de la primera linea con parametros globales
    if (!(archivo >> n >> m >> W)){
        std::cerr << "Error: Formato invalido en la primera linea del archivo\n";
        return nullptr;
    }

    // Gestionamos memoria de manera segura utilizando punteros unicos
    auto grafo = std::make_unique<Grafo>(n, m, W);

    // Lectura de cada arista iterando m veces
    for (int k = 0; k < m; ++k){
        int i, j, wij, pij;
        if (!(archivo >> i >> j >> wij >> pij)){
            std::cerr << "Error: Formato invalido o lineas insuficientes al leer las aristas\n";
            return nullptr;
        }
        // Insertamos la arista en la estructura subyacente
        grafo->agregarArista(i, j, wij, pij);
    }

    // Cerramos el flujo para liberar recursos del sistema
    archivo.close();
    std::cout << "Archivo parseado exitosamente\n";
    
    return grafo;
}

// Funcion auxiliar para mostrar las opciones disponibles al usuario
void mostrarMenu(){
    std::cout << "\n Menu Principal \n";
    std::cout << "1. Cargar un archivo de configuracion del grafo\n";
    std::cout << "2. Ejecutar el mejor algoritmo propuesto\n";
    std::cout << "3. Seleccionar un algoritmo especifico\n";
    std::cout << "4. Recibir del teclado un camino e imprimir el valor de peso total y beneficio total\n";
    std::cout << "5. Salir\n";
    std::cout << "Ingrese su opcion: ";
}

int main(){
    // Puntero inteligente que controlara el ciclo de vida del Grafo instanciado
    std::unique_ptr<Grafo> grafoPrincipal = nullptr;
    int opcion = 0;

    // Ciclo principal que mantiene viva la interfaz
    do {
        mostrarMenu();
        
        // Proteccion contra ingresos no numericos en la consola
        if (!(std::cin >> opcion)){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida, intente de nuevo\n";
            continue;
        }

        switch (opcion){
            case 1: {
                std::cout << "Ingrese la ruta del archivo: ";
                std::string ruta;
                std::cin >> ruta;
                
                // Intentamos cargar el grafo y si tiene exito reemplazamos el anterior
                auto nuevoGrafo = cargarGrafo(ruta);
                if (nuevoGrafo){
                    grafoPrincipal = std::move(nuevoGrafo);
                    std::cout << "Grafo cargado y asignado en memoria\n";
                }
                break;
            }
            case 2:
                // Placeholder para ejecutar la metaheuristica top tier
                if (!grafoPrincipal){
                    std::cout << "Se debe cargar un grafo primero\n";
                } else {
                    std::cout << "Ejecutando el mejor algoritmo propuesto\n";
                }
                break;
            case 3:
                // Placeholder para selector de algoritmos
                if (!grafoPrincipal){
                    std::cout << "Advertencia: Debe cargar un grafo primero\n";
                } else {
                    std::cout << "Seleccionar un algoritmo especifico (Placeholder)\n";
                }
                break;
            case 4:
                // Placeholder para validacion manual de solucion
                if (!grafoPrincipal){
                    std::cout << "Advertencia: Debe cargar un grafo primero\n";
                } else {
                    std::cout << "Recibir del teclado un camino e imprimir el valor de peso total y beneficio total (Placeholder)\n";
                }
                break;
            case 5:
                // Finaliza el bucle y la ejecucion del programa
                std::cout << "Saliendo del programa\n";
                break;
            default:
                std::cout << "Opcion fuera de rango\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}
