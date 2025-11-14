#pragma once
#include <string>
#include <iostream>
using namespace std;

class Fecha {
private:
    int anio;
    int mes;
    int dia;

public:
    // ----- Constructores -----
    Fecha();
    Fecha(int anio, int mes, int dia);
    Fecha(const string& fechaStr); //formato esperado: "YYYYMMDD"

    // ----- Getters -----
    int getAnio() const;
    int getMes() const;
    int getDia() const;

    // Setters
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // ----- Métodos útiles -----
    void mostrar() const;
    string toString() const;
    bool esValida() const;

    // ----- Operadores -----
    bool operator==(const Fecha& otra) const;
    bool operator!=(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    // Operador de salida para debug / impresión
    friend ostream& operator<<(ostream& os, const Fecha& f);

};
