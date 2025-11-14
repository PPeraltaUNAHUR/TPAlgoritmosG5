#pragma once
#include <string>
#include <iostream>
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
    Envio(string codCentro, int idPaquete, int idCliente, Fecha fecha, double peso, int prioridad);
    ~Envio();

    string getCodigoCentro() const;
    int getIdPaquete() const;
    int getIdCliente() const;
    const Fecha& getFecha() const;
    double getPeso() const;
    int getPrioridad() const;

    void setCodigoCentro(string codCentro);
    void setIdPaquete(int idPaquete);
    void setIdCliente(int idCliente);
    void setFecha(const Fecha& fecha);
    void setPeso(double peso);
    void setPrioridad(int prioridad);

    void mostrarInfo() const;
};