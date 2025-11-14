#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

class Camino {
private:
    vector<string> nodos;
    int distanciaTotal;

public:
    Camino();
    Camino(const vector<string>& nodos, int distanciaTotal);
    ~Camino();

    const vector<string>& getNodos() const;
    int getDistanciaTotal() const;

    void setNodos(const vector<string>& nuevosNodos);
    void setDistanciaTotal(int distancia);

    void agregarNodo(const string& nodo);
    void limpiar();
    int tamanio() const;
    void mostrar() const;
};
