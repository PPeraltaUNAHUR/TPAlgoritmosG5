#pragma once
#include <string>
#include <vector>
#include "Centro.h"
#include "Envio.h"
#include "Grafo.h"
#include "TablaHash.h"
#include "ABB.h"
#include "Camino.h"
#include "Fecha.h"

using namespace std;

class SistemaLogistica {
private:
    // Estructuras principales
    TablaHash<string, Centro*> centros;
    Grafo red;
    
    // Índices para búsquedas y análisis
    TablaHash<string, ABB<Fecha, vector<Envio>>> enviosPorCentro;
    TablaHash<string, vector<Envio>> indicePaquetes;
    TablaHash<string, vector<Envio>> indiceClientes;

public:
    // ----- Constructores / Destructor -----
    SistemaLogistica();
    ~SistemaLogistica();

    // ----- Gestión de Centros -----
    void cargarCentros(const string& ruta);
    void cargarConexiones(const string& ruta);
    void cargarEnvios(const string& ruta);

    bool agregarCentro(const Centro& centro);
    bool eliminarCentro(const string& codigo);
    Centro* obtenerCentro(const string& codigo);
    vector<Centro*> listarCentros(const string& criterio);

    // ----- Rutas y caminos -----
    Camino caminoMinimo(const string& origen, const string& destino);

    // ----- Análisis de Envíos -----
    vector<Envio> enviosEnRango(const string& codigo, const Fecha& desde, const Fecha& hasta);
    vector<Centro*> detectarSobrecarga(int maximo);
    vector<Envio> buscarPorPaquete(int idPaquete);

    // ----- Utilidades -----
    void mostrarResumenGeneral() const;
};
