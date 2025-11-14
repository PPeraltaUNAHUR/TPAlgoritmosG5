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
    string getCodigo() const;                       // El compilador te puede dar error, porque una función marcada como const no puede alterar el estado del objeto, esto solo es aclaración de como funciona el const.
    string getNombre() const;
    string getCiudad() const;
    int getCapacidad() const;
    int getEnviosDiarios() const;
    int getEmpleados() const;

    // Setters
    void setCodigo(string cod);
    void setNombre(string nom);
    void setCiudad(string ciudad);
    void setCapacidad(int cap);

    //Verificar si son necesarios los siguientes setters
    void setEnviosDiarios(int env);
    void setEmpleados(int emp);

    // Otros métodos
    void mostrarInfo() const;                    // Muestra la información del centro por consola

};


 
 