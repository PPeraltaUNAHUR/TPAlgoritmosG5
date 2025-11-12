#include "Paquete.h"

Paquete::Paquete(int id, double peso, double valor)
    : id(id), peso(peso), valor(valor) {}

int Paquete::getId() const { return id; }
double Paquete::getPeso() const { return peso; }
double Paquete::getValor() const { return valor; }