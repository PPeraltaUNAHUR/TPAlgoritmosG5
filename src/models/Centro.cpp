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

string Centro::getCodigo() const { return codigo; }
string Centro::getNombre() const { return nombre; }
string Centro::getCiudad() const { return ciudad; }
int Centro::getCapacidad() const { return capacidad; }
int Centro::getEnviosDiarios() const { return enviosDiarios; }
int Centro::getEmpleados() const { return empleados; }

// Setters 
void Centro::setCodigo(string cod) { codigo = cod; }
void Centro::setNombre(string nom) { nombre = nom; }
void Centro::setCiudad(string ciu) { ciudad = ciu; }
//void Centro::setCapacidad(int cap) { capacidad = cap; }
void Centro::setCapacidad(int cap) { 
    if (cap >= 0) capacidad = cap; 
}

// Verificar si son necesarios los siguientes setters
//void Centro::setEnviosDiarios(int env) { enviosDiarios = env; }
//void Centro::setEmpleados(int emp) { empleados = emp; }
void Centro::setEnviosDiarios(int env) { 
    if (env >= 0) enviosDiarios = env; 
}
void Centro::setEmpleados(int emp) { 
    if (emp >= 0) empleados = emp; 
}


// Otros métodos
void Centro::mostrarInfo() const {
    cout << "Centro de Distribucion" << endl;       //endl agrega un salto de línea después de imprimir
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Capacidad: " << capacidad << endl; 
    cout << "Envios Diarios: " << enviosDiarios << endl;
    cout << "Empleados: " << empleados << endl;


}