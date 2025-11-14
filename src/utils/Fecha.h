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
    Fecha();
    Fecha(int anio, int mes, int dia);
    Fecha(const string& fechaStr);

    int getAnio() const;
    int getMes() const;
    int getDia() const;

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    void mostrar() const;
    string toString() const;
    bool esValida() const;

    bool operator==(const Fecha& otra) const;
    bool operator!=(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    friend ostream& operator<<(ostream& os, const Fecha& f);

};
