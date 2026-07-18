#include "Grafo.h"
#include <queue>
#include <functional>
#include <stdexcept>

// Constructor llamado Grafo
// Luego de : inicializamos directamente las variables con su respectivo valor
Grafo::Grafo(int n, int m, int W): numNodos(n), numAristas(m), capacidad(W){
    
    // La lista de adyacencia debe de poder contener la cantidad de nodos a trabajar
    listaAdyacencia.resize(numNodos);

    // Inicializar el vector de distancias minimas con valores maximos posibles
    distanciasMinimas.assign(numNodos, std::numeric_limits<int>::max());

}

// Metodo para agregar aristas al grafo
void Grafo::agregarArista(int origen, int destino, int peso, int beneficio){
    
    // Caso base y validacion para evitar errores en el programa
    if(origen < 0 || origen >= numNodos || destino < 0 || destino >= numNodos){
        throw std::out_of_range("El origen o destino de la arista esta fuera de rango");
    }

    // Agregar la arista a la lista de adyacencia
    listaAdyacencia[origen].push_back({destino, peso, beneficio});
}

// Retorna una referencia constante a los vecinos del nodo
const std::vector<Arista>& Grafo::obtenerVecinos(int nodo) const{
    // Acceso directo a los vecinos del nodo
    return listaAdyacencia[nodo];
}

// Metodo para obtener el numero de nodos
int Grafo::getNumNodos() const{
    return numNodos;
}

// Metodo para obtener la capacidad del grafo
int Grafo::getCapacidadW() const{
    return capacidadW;
}

// Metodo para obtener la distancia minima al nodo de salida
int Grafo::getDistanciaMinima(int nodo) const{
    return distanciasMinimas[nodo];
}

// Metodo para calcular la distancia minima desde cualquier nodo hacia el nodo de salida
// Utiliza el algoritmo de Dijkstra
void Grafo::precalcularDijkstra(int nodoSalida){
    // Construimos el grafo transpuesto o con aristas invertidas
    // Calcula la ruta minima hacia el nodo de salida con un grafo dirigido
    std::vector<std::vector<std::pair<int, int>>> listaInversa(numNodos);
    for(int i = 0; i < numNodos; ++i){
        for(const auto& arista : listaAdyacencia[i]){
            // Almacenamos {nodoOrigen, peso} en la lista del nodoDestino
            listaInversa[arista.destino].push_back({i, arista.peso});
        }
    }


    // Iniciamos una cola de prioridad con el nodo de salida
    // Utilizamos el std::prioriti_queue para obtener el camino minimo
    // El par subyacente sera:{distanciaAcumulada, idNodo}
    using ParDistanciaNodo = std::pair<int, int>;
    std::priority_queue<ParDistanciaNodo, std::vector<ParDistanciaNodo>, std::greater<ParDistanciaNodo>> pq;

    // Reseteamos las distancias del vector de estado e inicializamos la raiz de busqueda
    distanciasMinimas.assign(numNodos, std::numeric_limits<int>::max());
    distanciasMinimas[nodoSalida] = 0;

    // Metemos el estado base o nodo de salida con distancia 0 dentro de la estructura
    minimos.push({0, nodoSalida});

    // Bucle principal del algoritmo de Dijkstra
    while(!minimos.empty()){
        // Obtenemos el nodo del borde con menor coste
        // Lo que tenemos dentro de minimos es la estructura par {distanciaAcumulada, idNodo}
        int distanciaActual = minimos.top().first;
        int nodoActual = minimos.top().second;
        minimos.pop(); // Para sacar el primer par contenido dentro de minimos

        // Descartamos el camino si ya encontramos uno mejor en el pasado
        if(distanciaActual > distanciasMinimas[nodoActual]){
            continue;
        }

        // Recorremos los vecinos del nodo actual
        for(const auto& vecino : listaInversa[nodoActual]){
            int nodoVecino = vecino.first;
            int pesoArista = vecino.second;
            int nuevaDistancia = distanciaActual + pesoArista;

            // Si encontramos un camino mas corto, actualizamos la distancia y agregamos a la cola de prioridad
            if(nuevaDistancia < distanciasMinimas[nodoVecino]){
                distanciasMinimas[nodoVecino] = nuevaDistancia;
                minimos.push({nuevaDistancia, nodoVecino});
            }
        }
    }

}