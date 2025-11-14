#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <filesystem>
#include "core/SistemaLogistica.h"
#include "core/Backtracking.h"
#include "models/Paquete.h"

using namespace std;

namespace {
    const string RUTA_CENTROS = "src/data/centros.txt";
    const string RUTA_CONEXIONES = "src/data/conexiones.txt";
    const string RUTA_ENVIOS = "src/data/envios.txt";
    const string DIRECTORIO_IMPORTS = "src/data/imports";
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEnteroSeguro(const string& mensaje, int minimo = numeric_limits<int>::min()) {
    while (true) {
        cout << mensaje;
        int valor;
        if (cin >> valor && valor >= minimo) {
            return valor;
        }
        cout << "Entrada inválida, intente nuevamente.\n";
        limpiarBuffer();
    }
}

double leerDoubleSeguro(const string& mensaje, double minimo = 0.0) {
    while (true) {
        cout << mensaje;
        double valor;
        if (cin >> valor && valor > minimo) {
            return valor;
        }
        cout << "Entrada inválida, ingrese un número mayor a " << minimo << ".\n";
        limpiarBuffer();
    }
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
    cout << "9. Agregar centro manualmente\n";
    cout << "10. Eliminar centro\n";
    cout << "11. Cargar centros desde directorio de importación\n";
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
    while (true) {
        string fechaStr;
        cout << mensaje << " (YYYYMMDD): ";
        cin >> fechaStr;
        Fecha fecha(fechaStr);
        if (fecha.esValida()) {
            return fecha;
        }
        cout << "Formato inválido de fecha.\n";
    }
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
        cout << left << setw(10) << centro->obtenerCodigo()
             << setw(20) << centro->obtenerNombre()
             << setw(15) << centro->obtenerCiudad()
             << setw(12) << centro->obtenerCapacidad()
             << setw(12) << centro->obtenerEnviosDiarios()
             << setw(12) << centro->obtenerEmpleados() << "\n";
    }
}

void mostrarCamino(SistemaLogistica& sistema) {
    string origen = leerCodigoCentro("Centro origen: ");
    string destino = leerCodigoCentro("Centro destino: ");
    if (!sistema.obtenerCentro(origen) || !sistema.obtenerCentro(destino)) {
        cout << "Alguno de los centros no existe en el sistema.\n";
        return;
    }
    Camino camino = sistema.caminoMinimo(origen, destino);
    if (camino.getNodos().empty()) {
        cout << "No se encontró un camino válido.\n";
        return;
    }
    camino.mostrar();
}

void mostrarEnviosEnRango(SistemaLogistica& sistema) {
    string centro = leerCodigoCentro("Centro a analizar: ");
    if (!sistema.obtenerCentro(centro)) {
        cout << "Centro inexistente.\n";
        return;
    }
    Fecha desde = leerFecha("Fecha desde");
    Fecha hasta = leerFecha("Fecha hasta");
    auto envios = sistema.enviosEnRango(centro, desde, hasta);
    cout << "Se encontraron " << envios.size() << " envíos.\n";
    for (const auto* envio : envios) {
        if (!envio) continue;
        envio->mostrarInfo();
        cout << "-----------------------------\n";
    }
}

void detectarSobrecarga(SistemaLogistica& sistema) {
    int maximo = leerEnteroSeguro("Máximo de envíos por semana permitido: ", 1);
    auto centros = sistema.detectarSobrecarga(maximo);
    if (centros.empty()) {
        cout << "No se detectaron centros con sobrecarga.\n";
        return;
    }
    cout << "Centros con sobrecarga:\n";
    for (const auto* centro : centros) {
        cout << " - " << centro->obtenerCodigo() << " (" << centro->obtenerNombre() << ")\n";
    }
}

void buscarPorPaquete(SistemaLogistica& sistema) {
    int id = leerEnteroSeguro("ID de paquete: ");
    auto envios = sistema.buscarPorPaquete(id);
    if (envios.empty()) {
        cout << "No se encontraron envíos para ese paquete.\n";
        return;
    }
    cout << envios.size() << " envíos encontrados:\n";
    for (const auto* envio : envios) {
        if (!envio) continue;
        envio->mostrarInfo();
        cout << "-----------------------------\n";
    }
}

void optimizarCarga(SistemaLogistica& sistema) {
    auto envios = sistema.obtenerEnvios();
    if (envios.empty()) {
        cout << "Debe cargar los envíos antes de optimizar.\n";
        return;
    }

    double capacidad = leerDoubleSeguro("Capacidad máxima del camión (kg): ", 0.0);

    vector<Paquete> paquetes;
    paquetes.reserve(envios.size());
    for (const auto* envio : envios) {
        if (!envio) continue;
        double valor = envio->getPrioridad() > 0 ? envio->getPrioridad() : envio->getPeso();
        paquetes.emplace_back(envio->getIdPaquete(), envio->getPeso(), valor);
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

void pausar() {
    cout << "\nPresione Enter para continuar...";
    limpiarBuffer();
    cin.get();
}

vector<string> listarArchivos(const string& directorio) {
    vector<string> archivos;
    std::error_code ec;
    if (!filesystem::exists(directorio, ec)) {
        return archivos;
    }
    for (const auto& entry : filesystem::directory_iterator(directorio)) {
        if (entry.is_regular_file()) {
            archivos.push_back(entry.path().string());
        }
    }
    sort(archivos.begin(), archivos.end());
    return archivos;
}

void agregarCentroCLI(SistemaLogistica& sistema) {
    limpiarBuffer();
    string codigo;
    string nombre;
    string ciudad;
    cout << "Código: ";
    getline(cin, codigo);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Ciudad: ";
    getline(cin, ciudad);

    int capacidad = leerEnteroSeguro("Capacidad: ", 0);
    int envios = leerEnteroSeguro("Envíos diarios estimados: ", 0);
    int empleados = leerEnteroSeguro("Cantidad de empleados: ", 0);

    Centro nuevo(codigo, nombre, ciudad, capacidad, envios, empleados);
    if (sistema.agregarCentro(nuevo)) {
        cout << "Centro agregado correctamente.\n";
    } else {
        cout << "Ya existe un centro con ese código.\n";
    }
}

void eliminarCentroCLI(SistemaLogistica& sistema) {
    string codigo = leerCodigoCentro("Código del centro a eliminar: ");
    if (sistema.eliminarCentro(codigo)) {
        cout << "Centro eliminado.\n";
    } else {
        cout << "No se encontró el centro solicitado.\n";
    }
}

void cargarCentrosExtraCLI(SistemaLogistica& sistema) {
    auto archivos = listarArchivos(DIRECTORIO_IMPORTS);
    if (archivos.empty()) {
        cout << "No se encontraron archivos en " << DIRECTORIO_IMPORTS << ".\n";
        return;
    }

    cout << "Archivos disponibles en " << DIRECTORIO_IMPORTS << ":\n";
    for (std::size_t i = 0; i < archivos.size(); ++i) {
        cout << "  " << (i + 1) << ") " << archivos[i] << "\n";
    }
    cout << "  0) Cancelar\n";

    int opcion = leerEnteroSeguro("Seleccione archivo: ", 0);
    if (opcion == 0 || opcion > static_cast<int>(archivos.size())) {
        cout << "Operación cancelada.\n";
        return;
    }

    const string& ruta = archivos[opcion - 1];
    sistema.cargarCentros(ruta);
    cout << "Centros adicionales cargados desde " << ruta << ".\n";
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
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1:
                listarSegunCriterio(sistema, "envios");
                pausar();
                break;
            case 2:
                listarSegunCriterio(sistema, "capacidad");
                pausar();
                break;
            case 3:
                listarSegunCriterio(sistema, "empleados");
                pausar();
                break;
            case 4:
                mostrarCamino(sistema);
                pausar();
                break;
            case 5:
                mostrarEnviosEnRango(sistema);
                pausar();
                break;
            case 6:
                detectarSobrecarga(sistema);
                pausar();
                break;
            case 7:
                buscarPorPaquete(sistema);
                pausar();
                break;
            case 8:
                optimizarCarga(sistema);
                pausar();
                break;
            case 9:
                agregarCentroCLI(sistema);
                pausar();
                break;
            case 10:
                eliminarCentroCLI(sistema);
                pausar();
                break;
            case 11:
                cargarCentrosExtraCLI(sistema);
                pausar();
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
