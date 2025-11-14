#include "Envio.h"
#include "../utils/Fecha.h"
#include <iostream>
using namespace std;

Envio::Envio() : codigoCentro(""), idPaquete(0), idCliente(0), fecha(), peso(0.0), prioridad(0) {}
Envio::Envio(string codCentro, int idPaquete, int idCliente,
             Fecha fecha, double peso, int prioridad)
    : codigoCentro(codCentro), idPaquete(idPaquete), idCliente(idCliente),
      fecha(fecha), peso(peso), prioridad(prioridad) {}
Envio::~Envio() {}

string Envio::getCodigoCentro() const { return codigoCentro; }
int Envio::getIdPaquete() const { return idPaquete; }
int Envio::getIdCliente() const { return idCliente; }
const Fecha& Envio::getFecha() const { return fecha; }
double Envio::getPeso() const { return peso; }
int Envio::getPrioridad() const { return prioridad; }

void Envio::setCodigoCentro(string codCentro) { codigoCentro = codCentro; }
void Envio::setIdPaquete(int idPaquete) { this->idPaquete = idPaquete; }
void Envio::setIdCliente(int idCliente) { this->idCliente = idCliente; }
void Envio::setFecha(const Fecha& fecha) { this->fecha = fecha; }
void Envio::setPeso(double peso) { this->peso = peso; }
void Envio::setPrioridad(int prioridad) { this->prioridad = prioridad; }

void Envio::mostrarInfo() const {
    cout << "Código Centro: " << codigoCentro << endl;
    cout << "ID Paquete: " << idPaquete << endl;
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Peso: " << peso << " kg" << endl;
    cout << "Prioridad: " << prioridad << endl;
}