#include "Camino.h"
#include <iostream>

// Constructor por defecto
Camino::Camino() : distanciaTotal(0) {}

// Constructor con parámetros
Camino::Camino(const vector<string>& nodos, int distanciaTotal)
    : nodos(nodos), distanciaTotal(distanciaTotal) {}

// Destructor
Camino::~Camino() {}

// Getters
const vector<string>& Camino::getNodos() const { return nodos; }
int Camino::getDistanciaTotal() const { return distanciaTotal; }

// Setters
void Camino::setNodos(const vector<string>& nuevosNodos) {
    nodos = nuevosNodos;
}

void Camino::setDistanciaTotal(int distancia) {
    distanciaTotal = distancia;
}

// Métodos útiles
void Camino::agregarNodo(const string& nodo) {
    nodos.push_back(nodo);
}

void Camino::limpiar() {
    nodos.clear();
    distanciaTotal = 0;
}

int Camino::tamanio() const {
    return nodos.size();
}

void Camino::mostrar() const {
    std::cout << "Camino: ";
    for (const auto& n : nodos)
        std::cout << n << " -> ";
    std::cout << "Fin" << std::endl;

    std::cout << "Distancia total: " << distanciaTotal << " km" << std::endl;
}
