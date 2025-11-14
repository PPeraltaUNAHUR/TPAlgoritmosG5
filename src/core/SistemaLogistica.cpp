#include "SistemaLogistica.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace {
    constexpr int BASE_TABLA = 211;
}

SistemaLogistica::SistemaLogistica()
    : centros(BASE_TABLA),
      red(),
      enviosPorCentro(BASE_TABLA),
      indicePaquetes(BASE_TABLA),
      indiceClientes(BASE_TABLA),
      enviosRegistrados() {}

SistemaLogistica::~SistemaLogistica() = default;

void SistemaLogistica::cargarCentros(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }

    string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::istringstream iss(linea);
        string codigo;
        string nombre;
        string ciudad;
        int capacidad = 0;
        int enviosDiarios = 0;
        int empleados = 0;

        if (!(iss >> codigo >> nombre >> ciudad >> capacidad >> enviosDiarios >> empleados)) {
            continue;
        }

        Centro centro(codigo, nombre, ciudad, capacidad, enviosDiarios, empleados);
        agregarCentro(centro);
    }
}

void SistemaLogistica::cargarConexiones(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }

    string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::istringstream iss(linea);
        string origen;
        string destino;
        int distancia = 0;

        if (!(iss >> origen >> destino >> distancia)) {
            continue;
        }

        red.agregarConexion(origen, destino, distancia);
    }
}

void SistemaLogistica::cargarEnvios(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }

    string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::istringstream iss(linea);
        string codigoCentro;
        int idPaquete = 0;
        int idCliente = 0;
        string fechaStr;
        double peso = 0.0;

        if (!(iss >> codigoCentro >> idPaquete >> idCliente >> fechaStr >> peso)) {
            continue;
        }

        Fecha fecha(fechaStr);
        if (!fecha.esValida()) {
            continue;
        }

        Envio envio(codigoCentro, idPaquete, idCliente, fecha, peso, 0);
        registrarEnvio(envio);
    }
}

bool SistemaLogistica::agregarCentro(const Centro& centro) {
    if (centros.contiene(centro.obtenerCodigo())) {
        return false;
    }

    centros.insertar(centro.obtenerCodigo(), centro);
    enviosPorCentro.insertar(centro.obtenerCodigo(), ABB<Fecha, vector<const Envio*>>{});
    return true;
}

bool SistemaLogistica::eliminarCentro(const string& codigo) {
    if (!centros.contiene(codigo)) {
        return false;
    }

    centros.eliminar(codigo);
    enviosPorCentro.eliminar(codigo);
    return true;
}

Centro* SistemaLogistica::obtenerCentro(const string& codigo) {
    return centros.obtener(codigo);
}

vector<Centro*> SistemaLogistica::listarCentros(const string& criterio) {
    vector<Centro*> resultado;
    string criterioNormalizado = normalizarCriterio(criterio);

    for (const auto& codigo : centros.claves()) {
        Centro* centro = centros.obtener(codigo);
        if (centro) {
            resultado.push_back(centro);
        }
    }

    auto comparador = [&](Centro* a, Centro* b) {
        if (criterioNormalizado == "capacidad") {
            return a->obtenerCapacidad() > b->obtenerCapacidad();
        }
        if (criterioNormalizado == "empleados") {
            return a->obtenerEmpleados() > b->obtenerEmpleados();
        }
        return a->obtenerEnviosDiarios() > b->obtenerEnviosDiarios();
    };

    std::sort(resultado.begin(), resultado.end(), comparador);
    return resultado;
}

Camino SistemaLogistica::caminoMinimo(const string& origen, const string& destino) {
    return red.calcularCaminoMinimo(origen, destino);
}

vector<const Envio*> SistemaLogistica::enviosEnRango(const string& codigo, const Fecha& desde, const Fecha& hasta) {
    vector<const Envio*> resultado;
    ABB<Fecha, vector<const Envio*>>* indice = enviosPorCentro.obtener(codigo);
    if (!indice) {
        return resultado;
    }

    vector<vector<const Envio*>> porFecha = indice->rango(desde, hasta);
    for (const auto& lista : porFecha) {
        resultado.insert(resultado.end(), lista.begin(), lista.end());
    }
    return resultado;
}

vector<Centro*> SistemaLogistica::detectarSobrecarga(int maximo) {
    vector<Centro*> resultado;

    for (const auto& codigo : centros.claves()) {
        ABB<Fecha, vector<const Envio*>>* indice = enviosPorCentro.obtener(codigo);
        if (!indice) continue;

        auto entradas = indice->entradas();
        vector<int> dias;
        vector<int> cantidades;
        dias.reserve(entradas.size());
        cantidades.reserve(entradas.size());

        for (const auto& entrada : entradas) {
            dias.push_back(fechaADias(entrada.first));
            cantidades.push_back(static_cast<int>(entrada.second.size()));
        }

        std::size_t izquierda = 0;
        int acumulado = 0;
        bool sobrecargado = false;

        for (std::size_t derecha = 0; derecha < dias.size(); ++derecha) {
            acumulado += cantidades[derecha];

            while (dias[derecha] - dias[izquierda] >= 7) {
                acumulado -= cantidades[izquierda];
                ++izquierda;
            }

            if (acumulado > maximo) {
                sobrecargado = true;
                break;
            }
        }

        if (sobrecargado) {
            Centro* centro = centros.obtener(codigo);
            if (centro) {
                resultado.push_back(centro);
            }
        }
    }

    return resultado;
}

vector<const Envio*> SistemaLogistica::buscarPorPaquete(int idPaquete) {
    vector<const Envio*>* envios = indicePaquetes.obtener(idPaquete);
    if (!envios) {
        return {};
    }
    return *envios;
}

void SistemaLogistica::registrarEnvio(const Envio& envio) {
    enviosRegistrados.push_back(std::make_unique<Envio>(envio));
    const Envio* punteroEnvio = enviosRegistrados.back().get();

    ABB<Fecha, vector<const Envio*>>* indiceCentro = enviosPorCentro.obtener(envio.getCodigoCentro());
    if (!indiceCentro) {
        enviosPorCentro.insertar(envio.getCodigoCentro(), ABB<Fecha, vector<const Envio*>>{});
        indiceCentro = enviosPorCentro.obtener(envio.getCodigoCentro());
    }

    vector<const Envio*>* enviosFecha = indiceCentro->buscar(envio.getFecha());
    if (!enviosFecha) {
        vector<const Envio*> lista{punteroEnvio};
        indiceCentro->insertar(envio.getFecha(), lista);
    } else {
        enviosFecha->push_back(punteroEnvio);
    }

    vector<const Envio*>* porPaquete = indicePaquetes.obtener(envio.getIdPaquete());
    if (!porPaquete) {
        indicePaquetes.insertar(envio.getIdPaquete(), vector<const Envio*>{punteroEnvio});
    } else {
        porPaquete->push_back(punteroEnvio);
    }

    vector<const Envio*>* porCliente = indiceClientes.obtener(envio.getIdCliente());
    if (!porCliente) {
        indiceClientes.insertar(envio.getIdCliente(), vector<const Envio*>{punteroEnvio});
    } else {
        porCliente->push_back(punteroEnvio);
    }
}

vector<const Envio*> SistemaLogistica::obtenerEnvios() const {
    vector<const Envio*> resultado;
    resultado.reserve(enviosRegistrados.size());
    for (const auto& ptr : enviosRegistrados) {
        resultado.push_back(ptr.get());
    }
    return resultado;
}

int SistemaLogistica::fechaADias(const Fecha& fecha) {
    int a = (14 - fecha.getMes()) / 12;
    int y = fecha.getAnio() + 4800 - a;
    int m = fecha.getMes() + 12 * a - 3;
    return fecha.getDia() + ((153 * m + 2) / 5) + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

string SistemaLogistica::normalizarCriterio(const string& criterio) {
    string resultado = criterio;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return resultado;
}

