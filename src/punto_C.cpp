#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include "core/Backtracking.h"
#include "models/Paquete.h"

int main()
{
    std::vector<Paquete> paquetes;
    std::string path = "src/data/envios.txt";
    std::ifstream in(path);

    std::vector<std::pair<int, double>> tmp;
    if (in)
    {
        std::string linea;
        while (std::getline(in, linea))
        {
            if (linea.empty())
                continue;

            std::istringstream iss(linea);
            std::string codigoCentro, idStr, clienteStr, fecha, pesoStr;
            if (!(iss >> codigoCentro >> idStr >> clienteStr >> fecha >> pesoStr))
                continue;

            int idPaquete = 0;
            double peso = 0.0;

            try
            {
                idPaquete = std::stoi(idStr);
            }
            catch (...)
            {
                continue;
            }

            try
            {
                peso = std::stod(pesoStr);
            }
            catch (...)
            {
                continue;
            }

            tmp.emplace_back(idPaquete, peso);
        }
    }

    for (const auto &pr : tmp)
    {
        int id = pr.first;
        double peso = pr.second;
        double valor = 0.0;
        while (true)
        {
            std::cout << "Ingrese un valor para el paquete id=" << id << " (peso=" << peso << "): ";
            if (!(std::cin >> valor))
            {
                std::cin.clear();
                std::string skip;
                std::getline(std::cin, skip);
                std::cout << "Entrada invalida. Ingrese un numero.\n";
                continue;
            }
            break;
        }
        paquetes.emplace_back(id, peso, valor);
    }

    if (paquetes.empty())
    {
        std::cout << "No hay paquetes";
        return 0;
    }

    double capacidadMaxima = 0.0;
    std::string lineaEntrada;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true)
    {
        std::cout << "Ingrese capacidad maxima (kg): ";
        if (!std::getline(std::cin, lineaEntrada))
        {
            std::cout << "\nError leyendo entrada. Saliendo.\n";
            return 1;
        }

        std::istringstream iss(lineaEntrada);
        double valor;
        if ((iss >> valor))
        {
            iss >> std::ws;
            if (iss.eof() && valor > 0.0)
            {
                capacidadMaxima = valor;
                break;
            }
        }

        std::cout << "Entrada invalida. Ingrese un numero positivo.\n";
    }

    std::cout << "Capacidad maxima: " << capacidadMaxima << " kg\n";

    Backtracking opt;
    auto resultado = opt.optimizar(paquetes, capacidadMaxima);

    std::cout << "\nMejor valor total: " << resultado.first << "\n";
    std::cout << "Paquetes seleccionados (ids): ";
    for (int id : resultado.second)
        std::cout << id << " ";
    std::cout << "\n";

    return 0;
}
