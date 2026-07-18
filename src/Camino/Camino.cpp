#include "Camino.h"
#include <stdexcept>

// Constructor
Camino::Camino(int totalNodos, int capacidad) {
    // Los acumuladores de estado inician en 0 dado que es un camino vacio
    pesoTotal = 0;
    beneficioTotal = 0;
    
    // Guardamos la restriccion rigida (W) del problema
    capacidadMaxima = capacidad;
    
    // Dimensionamos el vector de booleanos al total de nodos del grafo con valor 'false' para que no ocurran redinemsionamientos
    // Garantiza que la busqueda en 'fueVisitado' sea de acceso directo por un puntero
    nodosVisitados.assign(totalNodos, false);
}

// Mutación: agregarNodo
void Camino::agregarNodo(int nodo, int pesoArista, int beneficioArista) {
    // 1. Insercion al final de la secuencia
    // std::vector::push_back opera en O(1) amortizado, lo que mantiene el rendimiento
    // optimo al construir la ruta nodo por nodo
    secuencia.push_back(nodo);
    
    // 2. Registro de NOLOOP
    // Marcamos directamente la posicion del ID del nodo como verdadera
    nodosVisitados[nodo] = true;
    
    // 3. Tracking de estado (aditivo)
    // Evitamos el recalculo total de la ruta limitandonos a sumar el diferencial
    // Esto nos permite evaluar la validez (peso) y calidad (beneficio) al instante
    pesoTotal += pesoArista;
    beneficioTotal += beneficioArista;
}

// Mutación: eliminarUltimoNodo
void Camino::eliminarUltimoNodo(int pesoArista, int beneficioArista) {
    // Verificacion de integridad: el backtracking no puede hacerse en un camino vacio
    if (secuencia.empty()) {
        throw std::underflow_error("Intento de eliminar un nodo de un camino vacio.");
    }
    
    // 1. Identificamos el nodo que sera eliminado mediante un acceso al ultimo elemento
    int ultimoNodo = secuencia.back();
    
    // 2. Extraccion del nodo.
    // std::vector::pop_back destruye el elemento al final y reduce el tamaño logico
    secuencia.pop_back();
    
    // 3. Reversion de NOLOOP.
    // El nodo vuelve a estar disponible (no visitado). Al igual que en la insercion, 
    // es una escritura directa a memoria
    nodosVisitados[ultimoNodo] = false;
    
    // 4. Tracking de estado (sustractivo)
    // Revertimos matematicamente el impacto de las aristas deshechas
    // Esto deja el estado exacto previo a la llamada a 'agregarNodo'
    pesoTotal -= pesoArista;
    beneficioTotal -= beneficioArista;
}

// Consulta: fueVisitado
bool Camino::fueVisitado(int nodo) const {
    // COMO: Indice directo sobre un vector preasignado
    // POR QUÉ: Si usáramos std::find iterando sobre 'secuencia', la complejidad
    // sería lineal O(V). Para metaheurísticas y Branch and Bound esto formaría un 
    // cuello de botella. Con el acceso directo por índice, obtenemos O(1) absoluto
    return nodosVisitados[nodo];
}

int Camino::obtenerPesoTotal() const {
    return pesoTotal;
}

int Camino::obtenerBeneficioTotal() const {
    return beneficioTotal;
}

const std::vector<int>& Camino::obtenerSecuencia() const {
    // Retornar un 'const &' permite lectura externa como lo es imprimir la ruta 
    // sin el costo de copia y sin romper el encapsulamiento de la clase
    return secuencia;
}

int Camino::obtenerCapacidadMaxima() const {
    return capacidadMaxima;
}
