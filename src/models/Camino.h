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
    // Constructores
    Camino();
    Camino(const vector<string>& nodos, int distanciaTotal);
    ~Camino();

    // Getters
    const vector<string>& getNodos() const;
    int getDistanciaTotal() const;

    // Setters
    void setNodos(const vector<string>& nuevosNodos);
    void setDistanciaTotal(int distancia);

    // Métodos útiles
    void agregarNodo(const string& nodo);
    void limpiar();
    int tamanio() const;
    void mostrar() const;
};
