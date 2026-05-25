# TDP Labopratorio 2

## Importante:

### Se debe usar:
- Heuristica
- POO
- Librerias STL
- Contenedores STL para las estructuras de datos


### Debe haber:
- 2 archivos por cada clase (.cpp y .h)
- Archivo makefile que compile el programa inicial y los test por separado
- Archivo main.cpp con menú
- Pdf del informe
- Ejemplos de entrada


### Se debe implementar:
- Algoritmos 2-OPT, BreakOut Search, Scatter Search, Branch and Bound con mejor heurı́stica
- Algoritmo con el mejor óptimo utilizando el método de Branch and Bound, con lı́mite de iteraciones y poda


### Eficiencia:
- Para todos los ejemplos, debe entregar un camino con un beneficio
mayor o igual al obtenido por el algoritmo de 2-OPT
- No debe caerse por un segmentation fault ni por errores en ningún archivo de entrada


#### Lo que entiendo XD:
- Hay varias variables: k, pk, wk y W
- k: Tunel(camino o arista)
- pk: Beneficio del tunel
- wk: Peso del tunel al extraer el beneficio
- W: Peso máximo que puede cargar(capacidad máxima)

- Se puede crear un grafo
- Cada tunel es una arista
- Cada nodo del grafo es un punto de interconexion entre aristas
- Hay nodo de entrada y salida (i=0 ; i=N)

- Se debe partir desde el nodo inicial (i=0) y llegar al nodo final (i=N)
- No se repiten nodos
- No se puede sobrepasar la capacidad W
- El camino con mayor beneficio es el que se busca

#### Restricciones:
- Peso maximo
- Inicie y finalice correctamente
- Los tuneles escogidos se encuentran interconectados

#### Representación del camino:
Se puede representar de dos maneras
- E: Aristas
- C = [k0, k1, k2, ..., kQ] donde K pertenece a E y tiene Q+1 pasos. C es una secuencia de aristas
- C = [0, v1, v2, ..., vQ+1, N] donde 0 y N son los nodos inicial y final respectivamente. C es una secuencia de nodos visitados


#### Qué se espera:
Encontrar una solucion no óptima pero si cercana a ella con un tiempo de ejecución razonable