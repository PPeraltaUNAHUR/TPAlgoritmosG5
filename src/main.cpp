#include <iostream>
#include "models/Centro.h"     // Incluye tu clase
using namespace std;

int main() {
    // Crear algunos centros de distribución usando el constructor con parámetros
    Centro c1("C001", "Deposito Norte", "Rosario", 5000, 120, 45);
    Centro c2("C002", "Deposito Sur", "Cordoba", 3000, 95, 30);
    Centro c3("C003", "Centro Capital", "Buenos Aires", 8000, 200, 60);

    // Mostrar la información inicial de los centros
    cout << "===== ESTADO INICIAL DE LOS CENTROS =====" << endl;
    c1.mostrarInfo();
    c2.mostrarInfo();
    c3.mostrarInfo();

    // Actualizar algunos valores usando los setters
    c1.setEnviosDiarios(150);
    c1.setEmpleados(50);

    // Mostrar nuevamente para ver los cambios
    cout << endl << "===== ESTADO ACTUALIZADO DEL CENTRO 1 =====" << endl;
    c1.mostrarInfo();

    // Pausar la consola (opcional, para Visual Studio)
    cout << endl << "Presione Enter para salir...";
    cin.get();

    return 0;
}
