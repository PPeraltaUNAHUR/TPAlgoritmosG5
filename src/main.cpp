#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include "core/SistemaLogistica.h"
#include "core/Backtracking.h"
#include "models/Paquete.h"

using namespace std;

namespace {
    const string RUTA_CENTROS = "src/data/centros.txt";
    const string RUTA_CONEXIONES = "src/data/conexiones.txt";
    const string RUTA_ENVIOS = "src/data/envios.txt";
}

void mostrarMenu() {
    cout << "\n=== Sistema de Logística ===\n";
    cout << "1. Listar centros (por envíos diarios)\n";
    cout << "2. Listar centros (por capacidad)\n";
    cout << "3. Listar centros (por empleados)\n";
    cout << "4. Camino mínimo entre centros\n";
    cout << "5. Envíos en rango por centro\n";
    cout << "6. Detectar sobrecarga semanal\n";
    cout << "7. Buscar envíos por paquete\n";
    cout << "8. Optimizar carga de camión (Backtracking)\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

string leerCodigoCentro(const string& mensaje) {
    cout << mensaje;
    string codigo;
    cin >> codigo;
    return codigo;
}

Fecha leerFecha(const string& mensaje) {
    string fechaStr;
    cout << mensaje << " (YYYYMMDD): ";
    cin >> fechaStr;
    return Fecha(fechaStr);
}

void listarSegunCriterio(SistemaLogistica& sistema, const string& criterio) {
    auto centros = sistema.listarCentros(criterio);
    if (centros.empty()) {
        cout << "No hay centros cargados.\n";
        return;
    }
    cout << left << setw(10) << "Codigo" << setw(20) << "Nombre" << setw(15) << "Ciudad"
         << setw(12) << "Capacidad" << setw(12) << "Envios" << setw(12) << "Empleados" << "\n";
    for (const auto* centro : centros) {
        cout << left << setw(10) << centro->getCodigo()
             << setw(20) << centro->getNombre()
             << setw(15) << centro->getCiudad()
             << setw(12) << centro->getCapacidad()
             << setw(12) << centro->getEnviosDiarios()
             << setw(12) << centro->getEmpleados() << "\n";
    }
}

void mostrarCamino(SistemaLogistica& sistema) {
    string origen = leerCodigoCentro("Centro origen: ");
    string destino = leerCodigoCentro("Centro destino: ");
    Camino camino = sistema.caminoMinimo(origen, destino);
    if (camino.getNodos().empty()) {
        cout << "No se encontró un camino válido.\n";
        return;
    }
    camino.mostrar();
}

void mostrarEnviosEnRango(SistemaLogistica& sistema) {
    string centro = leerCodigoCentro("Centro a analizar: ");
    Fecha desde = leerFecha("Fecha desde");
    Fecha hasta = leerFecha("Fecha hasta");
    auto envios = sistema.enviosEnRango(centro, desde, hasta);
    cout << "Se encontraron " << envios.size() << " envíos.\n";
    for (const auto& envio : envios) {
        envio.mostrarInfo();
        cout << "-----------------------------\n";
    }
}

void detectarSobrecarga(SistemaLogistica& sistema) {
    int maximo;
    cout << "Máximo de envíos por semana permitido: ";
    cin >> maximo;
    auto centros = sistema.detectarSobrecarga(maximo);
    if (centros.empty()) {
        cout << "No se detectaron centros con sobrecarga.\n";
        return;
    }
    cout << "Centros con sobrecarga:\n";
    for (const auto* centro : centros) {
        cout << " - " << centro->getCodigo() << " (" << centro->getNombre() << ")\n";
    }
}

void buscarPorPaquete(SistemaLogistica& sistema) {
    int id;
    cout << "ID de paquete: ";
    cin >> id;
    auto envios = sistema.buscarPorPaquete(id);
    if (envios.empty()) {
        cout << "No se encontraron envíos para ese paquete.\n";
        return;
    }
    cout << envios.size() << " envíos encontrados:\n";
    for (const auto& envio : envios) {
        envio.mostrarInfo();
        cout << "-----------------------------\n";
    }
}

void optimizarCarga(SistemaLogistica& sistema) {
    const auto& envios = sistema.obtenerEnvios();
    if (envios.empty()) {
        cout << "Debe cargar los envíos antes de optimizar.\n";
        return;
    }

    double capacidad;
    cout << "Capacidad máxima del camión (kg): ";
    cin >> capacidad;

    vector<Paquete> paquetes;
    paquetes.reserve(envios.size());
    for (const auto& envio : envios) {
        double valor = envio.getPrioridad() > 0 ? envio.getPrioridad() : envio.getPeso();
        paquetes.emplace_back(envio.getIdPaquete(), envio.getPeso(), valor);
    }

    Backtracking opt;
    auto resultado = opt.optimizar(paquetes, capacidad);

    cout << "Mejor valor total: " << resultado.first << "\n";
    cout << "Paquetes seleccionados: ";
    for (int id : resultado.second) {
        cout << id << " ";
    }
    cout << "\n";
}

int main() {
    SistemaLogistica sistema;
    sistema.cargarCentros(RUTA_CENTROS);
    sistema.cargarConexiones(RUTA_CONEXIONES);
    sistema.cargarEnvios(RUTA_ENVIOS);

    bool salir = false;
    while (!salir) {
        mostrarMenu();
        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                listarSegunCriterio(sistema, "envios");
                break;
            case 2:
                listarSegunCriterio(sistema, "capacidad");
                break;
            case 3:
                listarSegunCriterio(sistema, "empleados");
                break;
            case 4:
                mostrarCamino(sistema);
                break;
            case 5:
                mostrarEnviosEnRango(sistema);
                break;
            case 6:
                detectarSobrecarga(sistema);
                break;
            case 7:
                buscarPorPaquete(sistema);
                break;
            case 8:
                optimizarCarga(sistema);
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }

    cout << "Hasta luego!\n";
    return 0;
}
