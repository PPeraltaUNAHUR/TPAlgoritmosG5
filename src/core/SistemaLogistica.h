#pragma once
#include <string>
#include <vector>
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

    //Estructuras principales
    TablaHash centros;
    Grafo red;
    
    //Índices para búsquedas y análisis
    TablaHash enviosPorCentro;
    TablaHash indicePaquetes;
    TablaHash indiceClientes;

public:
    //Constructor.

    SistemaLogistica();
    ~SistemaLogistica();    
    
    //Centros.

    void cargarCentros(const string& ruta);
    void cargarConexiones(const string& ruta);
    void cargarEnvios(const string& ruta);
    bool agregarCentro(const Centro& centro);
    bool eliminarCentro(const string& codigo);
    Centro* obtenerCentro(const string& codigo);
    vector<Centro*> listarCentros(const string& criterio);

    //Caminos.

    Camino caminoMinimo(const string& origen, const string& destino);

    //Métodos de envíos.

    vector<Envio> enviosEnRango(const string& codigo, const Fecha& desde, const Fecha& hasta);
    vector<Centro*> detectarSobrecarga(int maximo);
    vector<Envio> buscarPorPaquete(int idPaquete);

};
