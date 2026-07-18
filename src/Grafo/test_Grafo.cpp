#include <iostream>
#include <cassert>
#include "Grafo.h"

int main() {
    // Instanciamos un Grafo con 5 nodos 4 aristas y capacidad 100
    Grafo g(5, 4, 100);

    // Verificamos la asignacion de numNodos y capacidadW
    assert(g.getNumNodos() == 5);
    assert(g.getCapacidadW() == 100);

    // Agregamos aristas
    g.agregarArista(0, 1, 10, 50);
    g.agregarArista(1, 2, 20, 30);
    g.agregarArista(2, 3, 15, 20);
    g.agregarArista(3, 4, 5, 10);

    // Verificamos que los vecinos se asignen correctamente
    const auto& vecinos1 = g.obtenerVecinos(1);
    assert(vecinos1.size() == 1);
    assert(vecinos1[0].destino == 2);
    assert(vecinos1[0].peso == 20);
    assert(vecinos1[0].beneficio == 30);

    // Verificamos el conteo manual de aristas iterando sobre los nodos para numAristas
    int totalAristas = 0;
    for (int i = 0; i < g.getNumNodos(); ++i) {
        totalAristas += g.obtenerVecinos(i).size();
    }
    assert(totalAristas == 4);

    // Imprime un mensaje de exito por consola indicando que las pruebas pasaron
    std::cout << "Pruebas de Grafo pasaron exitosamente\n";
    
    return 0;
}
