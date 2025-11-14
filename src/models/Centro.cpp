#include "Centro.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Centro::Centro() : codigo(""), nombre(""), ciudad(""), capacidad(0), enviosDiarios(0), empleados(0) {} 

// Constructor con parámetros
Centro::Centro(string cod, string nom, string ciu, int cap, int env, int emp)
    : codigo(cod), nombre(nom), ciudad(ciu), capacidad(cap), enviosDiarios(env), empleados(emp) {}

// Destructor
Centro::~Centro() {} 

// Getters

string Centro::obtenerCodigo() const { return codigo; }
string Centro::obtenerNombre() const { return nombre; }
string Centro::obtenerCiudad() const { return ciudad; }
int Centro::obtenerCapacidad() const { return capacidad; }
int Centro::obtenerEnviosDiarios() const { return enviosDiarios; }
int Centro::obtenerEmpleados() const { return empleados; }

// Setters 
void Centro::establecerCodigo(string cod) { codigo = cod; }
void Centro::establecerNombre(string nom) { nombre = nom; }
void Centro::establecerCiudad(string ciu) { ciudad = ciu; }
void Centro::establecerCapacidad(int cap) { 
    if (cap >= 0) capacidad = cap; 
}

void Centro::establecerEnviosDiarios(int env) { 
    if (env >= 0) enviosDiarios = env; 
}
void Centro::establecerEmpleados(int emp) { 
    if (emp >= 0) empleados = emp; 
}


// Otros métodos
void Centro::mostrarInformacion() const {
    cout << "Centro de Distribucion" << endl;       //endl agrega un salto de línea después de imprimir
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Capacidad: " << capacidad << endl; 
    cout << "Envios Diarios: " << enviosDiarios << endl;
    cout << "Empleados: " << empleados << endl;


}
