#pragma once
#include <string>

class Paquete
{
public:
    Paquete() = default;
    Paquete(int id, double peso, double valor);

    int getId() const;
    double getPeso() const;
    double getValor() const;
private:
    int id{0};
    double peso{0.0};
    double valor{0.0};
};
