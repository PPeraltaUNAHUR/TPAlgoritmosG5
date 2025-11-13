#pragma once
#include <vector>
#include "../models/Paquete.h"

class Backtracking
{
public:
    Backtracking() = default;

    std::pair<double, std::vector<int>> optimizar(const std::vector<Paquete> &paquetes, double capacidadMaxima);

private:
    struct Nodo
    {
        int id;
        double peso;
        double valor;
        Nodo *padre{nullptr};
        std::vector<Nodo *> hijos;

        Nodo(int id_, double peso_, double valor_, Nodo *padre_ = nullptr)
            : id(id_), peso(peso_), valor(valor_), padre(padre_) {}
    };

    void backtrack(const std::vector<Paquete> &paquetes,
                   int start,
                   double pesoActual,
                   double valorActual,
                   double capacidadMaxima,
                   Nodo *arbol);

    // Liberar recursivamente los nodos del árbol combinatorio
    void liberarNodo(Nodo *node);

    double mejorValor{0.0};

    std::vector<int> mejorCombinacion;
};
