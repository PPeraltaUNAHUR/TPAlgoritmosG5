#include "Arista.h"

Arista::Arista() : destino(""), distancia(0) {}

Arista::Arista(const string& destino, int distancia)
    : destino(destino), distancia(distancia) {}

const string& Arista::getDestino() const {
    return destino;
}

int Arista::getDistancia() const {
    return distancia;
}

void Arista::setDestino(const string& nuevoDestino) {
    destino = nuevoDestino;
}

void Arista::setDistancia(int nuevaDistancia) {
    distancia = nuevaDistancia;
}

