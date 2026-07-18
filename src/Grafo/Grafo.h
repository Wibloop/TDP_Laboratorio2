#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <limits>
#include <stdexcept>

// Estructura de dato para representar una arista con peso y beneficio
struct Arista{
    int destino;
    int peso;
    int beneficio;
};

class Grafo{
    private:
        int numNodos;
        int numAristas;
        int capacidadW;
        std::vector<std::vector<Arista>> listaAdyacencia;

        std::vector<int> distanciasMinimas;
        // Almacena costo del camino minimo en peso hacia el nodo de salida (i=N)

    public:
        // Constructor
        Grafo(int n, int m, int W);
        ~Grafo() = default;

        // Agregar una arista
        void agregarArista(int origen, int destino, int peso, int beneficio);

        // Retorno por referencia constante para evitar las copias
        const std::vector<Arista>& obtenerVecinos(int nodo) const;

        // Obtener la capacidad y el numero de los nodos
        int getNumNodos() const;
        int getCapacidadW() const;

        // Metodos para el acotamiento Branch and Bound
        int getDistanciaMinima(int nodo) const;
        void precalcularDijkstra(int nodoSalida);

};

#endif // GRAFO_H