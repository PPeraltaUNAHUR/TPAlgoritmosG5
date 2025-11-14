#include "Camino.h"
#include <iostream>

Camino::Camino() : distanciaTotal(0) {}

Camino::Camino(const vector<string>& nodos, int distanciaTotal)
    : nodos(nodos), distanciaTotal(distanciaTotal) {}

Camino::~Camino() {}

const vector<string>& Camino::getNodos() const { return nodos; }
int Camino::getDistanciaTotal() const { return distanciaTotal; }

void Camino::setNodos(const vector<string>& nuevosNodos) {
    nodos = nuevosNodos;
}

void Camino::setDistanciaTotal(int distancia) {
    distanciaTotal = distancia;
}

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
