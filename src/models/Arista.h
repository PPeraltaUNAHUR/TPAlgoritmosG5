#pragma once
#include <string>

using namespace std;

class Arista {
private:
    string destino;
    int distancia;

public:
    Arista();
    Arista(const string& destino, int distancia);

    const string& getDestino() const;
    int getDistancia() const;

    void setDestino(const string& nuevoDestino);
    void setDistancia(int nuevaDistancia);
};