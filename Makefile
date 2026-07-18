CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Regla por defecto para compilar los ejecutables
all: test_grafo test_camino

# Regla para compilar el objeto Grafo
src/Grafo/Grafo.o: src/Grafo/Grafo.cpp src/Grafo/Grafo.h
	$(CXX) $(CXXFLAGS) -c src/Grafo/Grafo.cpp -o src/Grafo/Grafo.o

# Regla para compilar el objeto Camino
src/Camino/Camino.o: src/Camino/Camino.cpp src/Camino/Camino.h
	$(CXX) $(CXXFLAGS) -c src/Camino/Camino.cpp -o src/Camino/Camino.o

# Regla para compilar el ejecutable test_grafo enlazando sus respectivos objetos
test_grafo: src/Grafo/test_Grafo.cpp src/Grafo/Grafo.o
	$(CXX) $(CXXFLAGS) src/Grafo/test_Grafo.cpp src/Grafo/Grafo.o -o test_grafo -Isrc/Grafo

# Regla para compilar el ejecutable test_camino enlazando sus respectivos objetos
test_camino: src/Camino/test_Camino.cpp src/Camino/Camino.o
	$(CXX) $(CXXFLAGS) src/Camino/test_Camino.cpp src/Camino/Camino.o -o test_camino -Isrc/Camino

# Regla para limpiar archivos generados
clean:
	rm -f src/Grafo/*.o src/Camino/*.o test_grafo test_camino
