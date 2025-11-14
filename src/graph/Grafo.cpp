#include "Grafo.h"
#include <algorithm>
#include "../structures/ColaPrioridad.h"

Grafo::Grafo() : adyacencias(101) {}

Grafo::~Grafo() = default;

void Grafo::agregarConexion(const string& origen, const string& destino, int peso) {
    if (peso < 0) {
        return;
    }

    auto agregarArista = [&](const string& desde, const string& hacia) {
        vector<Arista>* lista = adyacencias.obtener(desde);
        if (!lista) {
            adyacencias.insertar(desde, vector<Arista>{});
            lista = adyacencias.obtener(desde);
        }
        lista->emplace_back(hacia, peso);
    };

    agregarArista(origen, destino);
    agregarArista(destino, origen);
}

vector<Arista> Grafo::obtenerConexiones(const string& codigo) {
    vector<Arista>* lista = adyacencias.obtener(codigo);
    if (!lista) {
        return {};
    }
    return *lista;
}

Camino Grafo::dijkstra(const string& origen, const string& destino) {
    Camino resultado;

    if (!adyacencias.obtener(origen) || !adyacencias.obtener(destino)) {
        return resultado;
    }

    struct NodoDist {
        string codigo;
        int distancia;
    };

    auto comparador = [](const NodoDist& a, const NodoDist& b) {
        return a.distancia < b.distancia;
    };

    ColaPrioridad<NodoDist, decltype(comparador)> cola(comparador);
    TablaHash<string, int> distancias(101);
    TablaHash<string, string> predecesores(101);
    TablaHash<string, bool> visitados(101);

    distancias.insertar(origen, 0);
    cola.insertar({origen, 0});

    while (!cola.vacia()) {
        NodoDist actual = cola.extraer();

        bool* yaVisitado = visitados.obtener(actual.codigo);
        if (yaVisitado && *yaVisitado) {
            continue;
        }
        visitados.insertar(actual.codigo, true);

        if (actual.codigo == destino) {
            break;
        }

        vector<Arista> vecinos = obtenerConexiones(actual.codigo);
        for (const auto& arista : vecinos) {
            int nuevaDist = actual.distancia + arista.getDistancia();
            int* distVecino = distancias.obtener(arista.getDestino());
            if (!distVecino || nuevaDist < *distVecino) {
                distancias.insertar(arista.getDestino(), nuevaDist);
                predecesores.insertar(arista.getDestino(), actual.codigo);
                cola.insertar({arista.getDestino(), nuevaDist});
            }
        }
    }

    int* distanciaDestino = distancias.obtener(destino);
    if (!distanciaDestino) {
        return resultado;
    }

    vector<string> nodos;
    string actual = destino;
    nodos.push_back(actual);

    while (actual != origen) {
        string* previo = predecesores.obtener(actual);
        if (!previo) {
            nodos.clear();
            return resultado;
        }
        actual = *previo;
        nodos.push_back(actual);
    }

    std::reverse(nodos.begin(), nodos.end());
    resultado.setNodos(nodos);
    resultado.setDistanciaTotal(*distanciaDestino);
    return resultado;
}

