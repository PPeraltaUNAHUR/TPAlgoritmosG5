#include "Fecha.h"
#include <iomanip>
#include <sstream>

Fecha::Fecha() : anio(0), mes(0), dia(0) {}
Fecha::Fecha(int anio, int mes, int dia): anio(anio), mes(mes), dia(dia) {}
Fecha::Fecha(const string& fechaStr) {
    // Espera formato "YYYYMMDD"
    if (fechaStr.size() != 8) {
        anio = mes = dia = 0;
        return;
    }

    anio = stoi(fechaStr.substr(0, 4));
    mes  = stoi(fechaStr.substr(4, 2));
    dia  = stoi(fechaStr.substr(6, 2));
}

// Getters
int Fecha::getAnio() const { return anio; }
int Fecha::getMes() const { return mes; }
int Fecha::getDia() const { return dia; }

// Setters
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

// Métodos útiles

bool Fecha::esValida() const {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));

    if (bisiesto && mes == 2)
        return dia <= 29;

    return dia <= diasMes[mes - 1];
}

void Fecha::mostrar() const {
    cout << toString() << endl;
}

string Fecha::toString() const {
    stringstream ss;
    ss << setw(4) << setfill('0') << anio << "-"
       << setw(2) << setfill('0') << mes  << "-"
       << setw(2) << setfill('0') << dia;
    return ss.str();
}


// Operadores

bool Fecha::operator==(const Fecha& otra) const {
    return anio == otra.anio && mes == otra.mes && dia == otra.dia;
}

bool Fecha::operator!=(const Fecha& otra) const {
    return !(*this == otra);
}

bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes  != otra.mes)  return mes  < otra.mes;
    return dia < otra.dia;
}

bool Fecha::operator>(const Fecha& otra) const {
    return otra < *this;
}

bool Fecha::operator<=(const Fecha& otra) const {
    return !(*this > otra);
}

bool Fecha::operator>=(const Fecha& otra) const {
    return !(*this < otra);
}

// Operador de salida
ostream& operator<<(ostream& os, const Fecha& f) {
    os << f.toString();
    return os;
}
