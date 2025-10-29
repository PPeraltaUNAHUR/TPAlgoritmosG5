#pragma once
#include <string>
#include "../utils/Fecha.h"

using namespace std;

class Envio {
private:
    string codigoCentro;
    int idPaquete;
    int idCliente;
    Fecha fecha;
    double peso;
    int prioridad;

public:
    Envio();
    ~Envio();
};