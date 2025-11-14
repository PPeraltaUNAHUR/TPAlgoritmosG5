#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../third_party/doctest.h"
#include "../structures/TablaHash.h"
#include "../models/Centro.h"
#include "../graph/Grafo.h"
#include "../core/SistemaLogistica.h"
#include "../core/Backtracking.h"
#include "../models/Paquete.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <string>

TEST_CASE("Inserción y obtención (string -> int)") {
    TablaHash<std::string, int> tabla(101);
    const std::string clave1 = "CBA";
    const std::string clave2 = "MZA";

    tabla.insertar(clave1, 1);
    tabla.insertar(clave2, 2);

    CHECK(tabla.contiene(clave1));
    CHECK(tabla.contiene(clave2));
    CHECK(tabla.tamanio() == 2);
    int* pValor = tabla.obtener(clave1);
    REQUIRE(pValor != nullptr);
    CHECK(*pValor == 1);
}

TEST_CASE("Eliminación") {
    TablaHash<std::string, int> tabla(101);
    const std::string clave = "CBA";
    tabla.insertar(clave, 42);

    tabla.eliminar(clave);

    CHECK(!tabla.contiene(clave));
    CHECK(tabla.obtener(clave) == nullptr);
    CHECK(tabla.tamanio() == 0);
}

TEST_CASE("Actualización (upsert)") {
    TablaHash<std::string, int> tabla(101);
    const std::string clave = "CBA";
    tabla.insertar(clave, 10);

    tabla.insertar(clave, 99);

    CHECK(tabla.contiene(clave));
    CHECK(tabla.tamanio() == 1);
    int* pValor = tabla.obtener(clave);
    REQUIRE(pValor != nullptr);
    CHECK(*pValor == 99);
}

TEST_CASE("Inserción y consulta (string -> Centro)") {
    TablaHash<std::string, Centro> tabla(101);
    const std::string clave = "CBA";
    Centro centro;

    tabla.insertar(clave, centro);

    CHECK(tabla.contiene(clave));
    CHECK(tabla.obtener(clave) != nullptr);
    CHECK(tabla.tamanio() == 1);
}

TEST_CASE("Grafo calcula camino minimo") {
    Grafo grafo;
    grafo.agregarConexion("A", "B", 5);
    grafo.agregarConexion("B", "C", 3);
    grafo.agregarConexion("A", "C", 20);
    grafo.agregarConexion("C", "D", 2);

    Camino camino = grafo.calcularCaminoMinimo("A", "D");
    CHECK(camino.getDistanciaTotal() == 10);
    REQUIRE(camino.getNodos().size() == 4);
    CHECK(camino.getNodos().front() == "A");
    CHECK(camino.getNodos().back() == "D");
}

namespace {
std::filesystem::path crearArchivoTemporal(const std::string& nombre,
                                           const std::string& contenido) {
    std::filesystem::path dir = std::filesystem::path("build/testdata");
    std::filesystem::create_directories(dir);
    std::filesystem::path archivo = dir / nombre;
    std::ofstream out(archivo);
    out << contenido;
    return archivo;
}
}

TEST_CASE("SistemaLogistica carga datos y consulta indices") {
    auto centrosPath = crearArchivoTemporal(
        "centros_test.txt",
        "BUE CentroBuenosAires BuenosAires 8000 200 60\n"
        "CBA CentroCordoba Cordoba 4000 120 40\n");
    auto conexionesPath = crearArchivoTemporal(
        "conexiones_test.txt",
        "BUE CBA 700\n");

    auto enviosPath = crearArchivoTemporal(
        "envios_test.txt",
        "BUE 1001 1 20250101 10.0\n"
        "BUE 1002 2 20250103 5.0\n"
        "CBA 2001 3 20250102 2.5\n");

    SistemaLogistica sistema;
    sistema.cargarCentros(centrosPath.string());
    sistema.cargarConexiones(conexionesPath.string());
    sistema.cargarEnvios(enviosPath.string());

    auto centrosOrdenados = sistema.listarCentros("capacidad");
    REQUIRE(centrosOrdenados.size() == 2);
    CHECK(centrosOrdenados.front()->obtenerCodigo() == "BUE");

    Fecha desde("20250101");
    Fecha hasta("20250105");
    auto enviosBue = sistema.enviosEnRango("BUE", desde, hasta);
    CHECK(enviosBue.size() == 2);

    auto sobrecargados = sistema.detectarSobrecarga(1);
    CHECK(!sobrecargados.empty());

    auto porPaquete = sistema.buscarPorPaquete(1002);
    REQUIRE(porPaquete.size() == 1);
    CHECK(porPaquete.front()->getIdCliente() == 2);
}

TEST_CASE("Backtracking selecciona mejor combinacion") {
    std::vector<Paquete> paquetes{
        {1, 3.0, 40.0},
        {2, 4.0, 50.0},
        {3, 5.0, 100.0},
        {4, 9.0, 120.0}
    };
    Backtracking opt;
    auto resultado = opt.optimizar(paquetes, 10.0);

    CHECK(resultado.first == doctest::Approx(150.0));
    REQUIRE(resultado.second.size() == 2);
    std::vector<int> ordenado = resultado.second;
    std::sort(ordenado.begin(), ordenado.end());
    CHECK(ordenado[0] == 2);
    CHECK(ordenado[1] == 3);
}


