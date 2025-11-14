#pragma once
#include <string>
#include <vector>
#include "../structures/TablaHash.h"
#include "../models/Camino.h"
#include "../models/Arista.h"

using namespace std;

class Grafo {
private:
    TablaHash<string, vector<Arista>> adyacencias;

public:
    Grafo();
    ~Grafo();
    void agregarConexion(const string& origen, const string& destino, int peso);
    vector<Arista> obtenerConexiones(const string& codigo);
    Camino calcularCaminoMinimo(const string& origen, const string& destino);
};