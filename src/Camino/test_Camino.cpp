#include <iostream>
#include <cassert>
#include "Camino.h"

int main() {
    // Instanciamos un Camino con 5 nodos y capacidad de 100
    Camino c(5, 100);

    // Verificamos estado inicial
    assert(c.obtenerPesoTotal() == 0);
    assert(c.obtenerBeneficioTotal() == 0);
    assert(c.obtenerCapacidadMaxima() == 100);

    // Simulamos la adicion de nodos
    c.agregarNodo(0, 0, 0);
    c.agregarNodo(2, 10, 20);
    c.agregarNodo(4, 15, 30);

    // Verificamos la actualizacion en O(1) del beneficio y peso total
    assert(c.obtenerPesoTotal() == 25);
    assert(c.obtenerBeneficioTotal() == 50);

    // Comprobamos estrictamente la restriccion NOLOOP usando assert
    assert(c.fueVisitado(0) == true);
    assert(c.fueVisitado(2) == true);
    assert(c.fueVisitado(4) == true);
    assert(c.fueVisitado(1) == false);
    assert(c.fueVisitado(3) == false);

    // Comprobamos el correcto funcionamiento al eliminar el ultimo nodo
    c.eliminarUltimoNodo(15, 30);
    assert(c.obtenerPesoTotal() == 10);
    assert(c.obtenerBeneficioTotal() == 20);
    assert(c.fueVisitado(4) == false);

    // Imprime un mensaje de exito por consola indicando que las pruebas pasaron
    std::cout << "Pruebas de Camino pasaron exitosamente\n";
    
    return 0;
}
