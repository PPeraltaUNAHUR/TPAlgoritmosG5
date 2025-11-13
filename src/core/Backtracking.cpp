#include "Backtracking.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

std::pair<double, std::vector<int>> Backtracking::optimizar(const std::vector<Paquete> &paquetes, double capacidadMaxima)
{
    mejorValor = 0.0;
    mejorCombinacion.clear();

    Backtracking::Nodo *arbol = new Backtracking::Nodo(-1, 0.0, 0.0, nullptr);
    std::vector<Paquete> ordenados = paquetes;
    std::sort(ordenados.begin(), ordenados.end(), [](const Paquete &a, const Paquete &b)
              { return a.getPeso() > b.getPeso(); });

    int n = static_cast<int>(ordenados.size());

    if (n == 0 || capacidadMaxima <= 0.0)
    {
        delete arbol;
        return {0.0, {}};
    }

    backtrack(ordenados, 0, 0.0, 0.0, capacidadMaxima, arbol);

    liberarNodo(arbol);

    return {mejorValor, mejorCombinacion};
}

void Backtracking::backtrack(const std::vector<Paquete> &paquetes,
                             int start,
                             double pesoActual,
                             double valorActual,
                             double capacidadMaxima,
                             Backtracking::Nodo *arbol)
{
    if (pesoActual > capacidadMaxima)
    {
        return;
    }

    if (valorActual > mejorValor)
    {
        mejorValor = valorActual;

        std::vector<int> solucion;
        Backtracking::Nodo *arbActual = arbol;

        while (arbActual && arbActual->padre)
        {
            solucion.push_back(arbActual->id);
            arbActual = arbActual->padre;
        }
        std::reverse(solucion.begin(), solucion.end());
        mejorCombinacion = std::move(solucion);
    }

    if (start >= static_cast<int>(paquetes.size()))
    {
        return;
    }

    for (int j = start; j < static_cast<int>(paquetes.size()); ++j)
    {
        const Paquete &p = paquetes[j];
        Backtracking::Nodo *hijo = new Backtracking::Nodo(p.getId(), p.getPeso(), p.getValor(), arbol);
        arbol->hijos.push_back(hijo);

        backtrack(paquetes, j + 1, pesoActual + p.getPeso(), valorActual + p.getValor(), capacidadMaxima, hijo);
    }
}

/**
 * Función para liberar recursivamente los nodos del árbol
 */
void Backtracking::liberarNodo(Backtracking::Nodo *node)
{
    if (!node)
        return;
    for (Backtracking::Nodo *h : node->hijos)
    {
        liberarNodo(h);
    }
    delete node;
}