#ifndef CAMINO_H
#define CAMINO_H

#include <vector>

/**
 * @class Camino
 * @brief Representa una solución candidata (ruta/camino) para el Orienteering Problem.
 *
 * Esta clase mantiene el estado actual de un camino, permitiendo operaciones
 * de inserción y eliminación de nodos en tiempo constante (O(1)). Esto es 
 * imperativo para algoritmos con alto nivel de iteración como Branch and Bound 
 * y metaheurísticas (Scatter Search, 2-OPT).
 */
class Camino {
private:
    /**
     * @brief Secuencia de nodos visitados en el camino.
     * 
     * Se utiliza un std::vector<int> porque necesitamos acceso secuencial rápido,
     * memoria contigua y la capacidad de agregar/eliminar al final en O(1) amortizado.
     * Modela la forma C = [0, v1, ..., vQ+1, N].
     */
    std::vector<int> secuencia;

    /**
     * @brief Mecanismo para verificar visitas en O(1) (NOLOOP).
     * 
     * std::vector<bool> mantiene un mapeo booleano directo donde el índice es el ID
     * del nodo. Evita la necesidad de iterar linealmente sobre 'secuencia' para saber
     * si un nodo genera un ciclo. Reduce la complejidad de búsqueda de O(V) a O(1).
     */
    std::vector<bool> nodosVisitados;

    /**
     * @brief Peso total acumulado del camino actual.
     * 
     * Su actualización O(1) al agregar/quitar nodos permite conocer el estado de la
     * restricción de capacidad (W) instantáneamente, sin tener que recalcular
     * iterando por las aristas de la secuencia.
     */
    int pesoTotal;

    /**
     * @brief Beneficio total acumulado del camino actual.
     * 
     * Mantenido en O(1) de manera aditiva, crucial para evaluar rápidamente la función
     * objetivo al transitar por el espacio de soluciones.
     */
    int beneficioTotal;

    /**
     * @brief Límite de peso máximo (W) permitido para este camino.
     * 
     * Es la restricción rígida que define la viabilidad del Orienteering Problem.
     */
    int capacidadMaxima;

public:
    /**
     * @brief Constructor de la clase Camino.
     * 
     * @param totalNodos Cantidad total de nodos en el Grafo (para dimensionar nodosVisitados).
     * @param capacidad Maxima capacidad o límite de peso (W) del problema.
     * 
     * La pre-dimensión de nodosVisitados asegura que no haya realojamiento de memoria
     * (realloc) durante la ejecución intensiva, manteniendo el tiempo de acceso estrictamente.
     */
    Camino(int totalNodos, int capacidad);

    /**
     * @brief Agrega un nuevo nodo al final del camino.
     * 
     * @param nodo El ID del nodo a agregar.
     * @param pesoArista El costo/peso de viajar al nuevo nodo.
     * @param beneficioArista El premio/beneficio recolectado en este nuevo nodo.
     * 
     * Mutación hacia adelante (forward mutation). Actualiza la secuencia, el 
     * tracking NOLOOP, y los acumuladores de estado en O(1).
     */
    void agregarNodo(int nodo, int pesoArista, int beneficioArista);

    /**
     * @brief Elimina el último nodo ingresado al camino.
     * 
     * @param pesoArista El costo/peso de la arista que conectaba con el último nodo.
     * @param beneficioArista El premio/beneficio del último nodo.
     * 
     * Mutación hacia atrás (backtracking). Fundamental para deshacer acciones al 
     * retroceder en el árbol de búsqueda (Branch and Bound) o revertir movimientos
     * de vecindarios (2-OPT) en O(1).
     */
    void eliminarUltimoNodo(int pesoArista, int beneficioArista);

    /**
     * @brief Verifica si un nodo ya forma parte del camino actual.
     * 
     * @param nodo ID del nodo a consultar.
     * @return true si el nodo ya está en la secuencia, false en caso contrario.
     * 
     * Resuelve el requerimiento NOLOOP en tiempo O(1) consultando el vector pre-dimensionado.
     */
    bool fueVisitado(int nodo) const;

    /**
     * @brief Obtiene el peso total actual del camino.
     * @return Entero con el peso acumulado.
     */
    int obtenerPesoTotal() const;

    /**
     * @brief Obtiene el beneficio total actual del camino.
     * @return Entero con el beneficio acumulado.
     */
    int obtenerBeneficioTotal() const;

    /**
     * @brief Obtiene la secuencia actual de nodos.
     * @return Referencia constante al vector de la secuencia (evita copias O(N)).
     */
    const std::vector<int>& obtenerSecuencia() const;

    /**
     * @brief Obtiene la capacidad máxima paramétrica del camino.
     * @return Capacidad W permitida.
     */
    int obtenerCapacidadMaxima() const;
};

#endif // CAMINO_H
