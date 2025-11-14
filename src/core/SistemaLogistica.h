#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../models/Centro.h"
#include "../models/Envio.h"
#include "../graph/Grafo.h"
#include "../structures/TablaHash.h"
#include "../structures/ABB.h"
#include "../models/Camino.h"
#include "../utils/Fecha.h"

using namespace std;

class SistemaLogistica {
private:
    TablaHash<string, Centro> centros;
    Grafo red;
    TablaHash<string, ABB<Fecha, vector<const Envio*>>> enviosPorCentro;
    TablaHash<int, vector<const Envio*>> indicePaquetes;
    TablaHash<int, vector<const Envio*>> indiceClientes;
    vector<std::unique_ptr<Envio>> enviosRegistrados;

    void registrarEnvio(const Envio& envio);
    static int fechaADias(const Fecha& fecha);
    static string normalizarCriterio(const string& criterio);

public:
    SistemaLogistica();
    ~SistemaLogistica();    
    
    void cargarCentros(const string& ruta);
    void cargarConexiones(const string& ruta);
    void cargarEnvios(const string& ruta);
    bool agregarCentro(const Centro& centro);
    bool eliminarCentro(const string& codigo);
    Centro* obtenerCentro(const string& codigo);
    vector<Centro*> listarCentros(const string& criterio);

    Camino caminoMinimo(const string& origen, const string& destino);

    vector<const Envio*> enviosEnRango(const string& codigo, const Fecha& desde, const Fecha& hasta);
    vector<Centro*> detectarSobrecarga(int maximo);
    vector<const Envio*> buscarPorPaquete(int idPaquete);
    vector<const Envio*> obtenerEnvios() const;
};
