#ifndef CAMINO_H
#define CAMINO_H

#include <vector>

/**
 * @class Camino
 * @brief Representa una solucion candidata (ruta/camino) para el Orienteering Problem descrito
 *
 * Esta clase mantiene el estado actual de un camino, permitiendo operaciones
 * de insercion y eliminacion de nodos
 */
class Camino {
private:
    /**
     * @brief Secuencia de nodos visitados en el camino
     * 
     * Se utiliza un std::vector<int> porque necesitamos acceso secuencial,
     * memoria contigua y la capacidad de agregar/eliminar al final
     * Modela la forma C = [0, v1, ..., vQ+1, N]
     */
    std::vector<int> secuencia;

    /**
     * @brief Mecanismo para verificar visitas
     * 
     * std::vector<bool> mantiene un mapeo booleano directo donde el indice es el ID
     * del nodo. Evita la necesidad de iterar linealmente sobre la secuencia para saber
     * si un nodo genera un ciclo.
     */
    std::vector<bool> nodosVisitados;

    /**
     * @brief Peso total acumulado del camino actual
     * 
     * Su actualizacion al agregar/quitar nodos permite conocer el estado de la
     * restriccion de capacidad (W) instantaneamente, sin tener que recalcular
     * iterando por las aristas de la secuencia
     */
    int pesoTotal;

    /**
     * @brief Beneficio total acumulado del camino actual
     */
    int beneficioTotal;

    /**
     * @brief Limite de peso maximo (W) permitido para este camino
     * 
     * Es la restriccion rigida que define la viabilidad del Orienteering Problem
     */
    int capacidadMaxima;

public:
    /**
     * @brief Constructor de la clase Camino
     * 
     * @param totalNodos Cantidad total de nodos en el Grafo (para dimensionar nodosVisitados)
     * @param capacidad Maxima capacidad o límite de peso (W) del problema
     * 
     * La pre-dimension de nodosVisitados asegura que no haya realojamiento de memoria
     * durante la ejecucion intensiva, manteniendo el tiempo de acceso estrictamente
     */
    Camino(int totalNodos, int capacidad);

    /**
     * @brief Agrega un nuevo nodo al final del camino
     * 
     * @param nodo El ID del nodo a agregar
     * @param pesoArista El costo/peso de viajar al nuevo nodo
     * @param beneficioArista El premio/beneficio recolectado en este nuevo nodo
     * 
     * Cambio hacia adelante, actualiza la secuencia y los acumuladores de estado
     */
    void agregarNodo(int nodo, int pesoArista, int beneficioArista);

    /**
     * @brief Elimina el ultimo nodo ingresado al camino
     * 
     * @param pesoArista El costo/peso de la arista que conectaba con el ultimo nodo
     * @param beneficioArista El premio/beneficio del ultimo nodo
     * 
     * Cambio hacia atras haciendo backtracking, fundamental para deshacer acciones al 
     * retroceder en el arbol de busqueda del Branch and Bound o revertir movimientos
     * de vecindarios del 2-OPT
     */
    void eliminarUltimoNodo(int pesoArista, int beneficioArista);

    /**
     * @brief Verifica si un nodo ya forma parte del camino actual
     * 
     * @param nodo ID del nodo a consultar
     * @return true si el nodo ya esta en la secuencia y false en caso contrario
     */
    bool fueVisitado(int nodo) const;

    /**
     * @brief Obtiene el peso total actual del camino
     * @return Entero con el peso acumulado
     */
    int obtenerPesoTotal() const;

    /**
     * @brief Obtiene el beneficio total actual del camino
     * @return Entero con el beneficio acumulado
     */
    int obtenerBeneficioTotal() const;

    /**
     * @brief Obtiene la secuencia actual de nodos
     * @return Referencia constante al vector de la secuencia
     */
    const std::vector<int>& obtenerSecuencia() const;

    /**
     * @brief Obtiene la capacidad maxima parametrica del camino
     * @return Capacidad W permitida
     */
    int obtenerCapacidadMaxima() const;
};

#endif // CAMINO_H
