#pragma once                                 // Evita inclusiones múltiples, por varios llamados a este mismo archivo
#include <string>

using namespace std;

class Centro {
private:
    string codigo;                           // Identificador único (por ejemplo, "C1", "C2")
    string nombre;                           // Nombre del centro (p.ej. "Depósito Córdoba")
    string ciudad;                           // Ciudad donde se encuentra el centro
    int capacidad;                           // Capacidad de almacenamiento (en unidades o kg)
    int enviosDiarios;
    int empleados;

public:
    // Constructores y destructor
    Centro();                                 // Constructor por defecto
    Centro(string cod, string nom, string ciu, int cap, int env, int emp);     // Constructor con parámetros
    ~Centro();                               // Destructor // Liberar recursos si es necesario //No hace nada en este caso ya que no hay memoria dinámica dentro del Centro

    // Getters
    string obtenerCodigo() const;
    string obtenerNombre() const;
    string obtenerCiudad() const;
    int obtenerCapacidad() const;
    int obtenerEnviosDiarios() const;
    int obtenerEmpleados() const;

    // Setters
    void establecerCodigo(string cod);
    void establecerNombre(string nom);
    void establecerCiudad(string ciudad);
    void establecerCapacidad(int cap);

    //Verificar si son necesarios los siguientes setters
    void establecerEnviosDiarios(int env);
    void establecerEmpleados(int emp);

    // Otros métodos
    void mostrarInformacion() const;

};


 
 