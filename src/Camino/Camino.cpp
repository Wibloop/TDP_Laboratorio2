#include "Camino.h"
#include <stdexcept>

// Constructor del camino
Camino::Camino(int totalNodos, int capacidad) {
    // Los acumuladores de estado inician en 0 dado que es un camino vacio
    pesoTotal = 0;
    beneficioTotal = 0;
    
    // Guardamos la restriccion rigida (W) del problema
    capacidadMaxima = capacidad;
    
    // Dimensionamos el vector de booleanos al total de nodos del grafo con valor false para que no ocurran redinemsionamientos
    // Garantiza que la busqueda en 'fueVisitado' sea de acceso directo por un puntero
    nodosVisitados.assign(totalNodos, false);
}

// Metodo agregarNodo
void Camino::agregarNodo(int nodo, int pesoArista, int beneficioArista) {
    // Insercion al final de la secuencia
    // std::vector::push_back sirve para insertar un elemento al final del vector
    // con el fin de agregar un nodo a nuestra solucion
    secuencia.push_back(nodo);
    
    // Marcamos directamente la posicion del ID del nodo como verdadera
    // Esto nos servira para verificar que no se repitan nodos dentro del camino
    nodosVisitados[nodo] = true;
    
    // Vemos el estado final y lo actualizamos para ver validez y calidad del camino
    // Sumamos el peso y el beneficio de la arista que acabamos de agregar
    pesoTotal += pesoArista;
    beneficioTotal += beneficioArista;
}

// Metodo eliminarUltimoNodo
void Camino::eliminarUltimoNodo(int pesoArista, int beneficioArista) {
    // El backtracking no puede hacerse en un camino vacio
    if (secuencia.empty()) {
        throw std::underflow_error("Intento de eliminar un nodo de un camino vacio");
    }
    
    // Identificamos el nodo que sera eliminado mediante un acceso al ultimo elemento
    int ultimoNodo = secuencia.back();
    
    // Extraccion del nodo
    // std::vector::pop_back destruye el elemento al final y reduce el tamaño logico
    secuencia.pop_back();
    
    // Revertimos el estado para que el nodo vuelva a estar disponible o no visitado
    nodosVisitados[ultimoNodo] = false;
    
    // Revertimos el impacto de las aristas deshechas
    // Esto deja el estado exacto anterior a la llamada a agregarNodo
    pesoTotal -= pesoArista;
    beneficioTotal -= beneficioArista;
}

// Metodo fueVisitado
bool Camino::fueVisitado(int nodo) const {
    // Acceso directo a la posicion del id del nodo, obtenemos el valor booleano
    return nodosVisitados[nodo];
}

// Metodo obtenerPesoTotal
int Camino::obtenerPesoTotal() const {
    // Obtenemos el peso acumulado del camino
    return pesoTotal;
}

// Metodo obtenerBeneficioTotal
int Camino::obtenerBeneficioTotal() const {
    // Obtenemos el beneficio acumulado del camino
    return beneficioTotal;
}

// Metodo obtenerSecuencia
const std::vector<int>& Camino::obtenerSecuencia() const {
    // Retornar un 'const &' permite lectura externa como lo es imprimir la ruta 
    // sin el costo de copia y sin romper el encapsulamiento de la clase
    return secuencia;
}

// Metodo obtenerCapacidadMaxima
int Camino::obtenerCapacidadMaxima() const {
    // Obtenemos la capacidad maxima del camino
    return capacidadMaxima;
}
