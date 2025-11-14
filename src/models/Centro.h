#pragma once
#include <string>

using namespace std;

class Centro {
private:
    string codigo;
    string nombre;
    string ciudad;
    int capacidad;
    int enviosDiarios;
    int empleados;

public:
    Centro();
    Centro(string cod, string nom, string ciu, int cap, int env, int emp);
    ~Centro();

    string obtenerCodigo() const;
    string obtenerNombre() const;
    string obtenerCiudad() const;
    int obtenerCapacidad() const;
    int obtenerEnviosDiarios() const;
    int obtenerEmpleados() const;

    void establecerCodigo(string cod);
    void establecerNombre(string nom);
    void establecerCiudad(string ciudad);
    void establecerCapacidad(int cap);
    void establecerEnviosDiarios(int env);
    void establecerEmpleados(int emp);
    void mostrarInformacion() const;
};


 
 