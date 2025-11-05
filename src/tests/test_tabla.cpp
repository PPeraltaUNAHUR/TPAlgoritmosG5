#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../third_party/doctest.h"
#include "../structures/TablaHash.h"
#include "../models/Centro.h"
#include <string>

TEST_CASE("Inserción y obtención (string -> int)") {
    // Given: una tabla vacía y dos entradas
    TablaHash<std::string, int> tabla(101);
    const std::string clave1 = "CBA";
    const std::string clave2 = "MZA";

    // When: inserto ambas claves con sus valores
    tabla.insertar(clave1, 1);
    tabla.insertar(clave2, 2);

    // Then: la tabla contiene las claves y los valores son correctos
    CHECK(tabla.contiene(clave1));
    CHECK(tabla.contiene(clave2));
    CHECK(tabla.tam() == 2);
    int* pValor = tabla.obtener(clave1);
    REQUIRE(pValor != nullptr);
    CHECK(*pValor == 1);
}

TEST_CASE("Eliminación") {
    // Given: una tabla con una clave
    TablaHash<std::string, int> tabla(101);
    const std::string clave = "CBA";
    tabla.insertar(clave, 42);

    // When: elimino la clave
    tabla.eliminar(clave);

    // Then: la clave ya no está presente
    CHECK(!tabla.contiene(clave));
    CHECK(tabla.obtener(clave) == nullptr);
    CHECK(tabla.tam() == 0);
}

TEST_CASE("Actualización (upsert)") {
    // Given: una tabla con una clave ya insertada
    TablaHash<std::string, int> tabla(101);
    const std::string clave = "CBA";
    tabla.insertar(clave, 10);

    // When: inserto nuevamente la misma clave con otro valor
    tabla.insertar(clave, 99);

    // Then: el valor se actualiza, no se duplica la entrada
    CHECK(tabla.contiene(clave));
    CHECK(tabla.tam() == 1);
    int* pValor = tabla.obtener(clave);
    REQUIRE(pValor != nullptr);
    CHECK(*pValor == 99);
}

TEST_CASE("Inserción y consulta (string -> Centro)") {
    // Given: una tabla de centros y un centro por defecto
    TablaHash<std::string, Centro> tabla(101);
    const std::string clave = "CBA";
    Centro centro; // Centro no expone campos públicos, validamos existencia

    // When: inserto el centro con su clave
    tabla.insertar(clave, centro);

    // Then: la clave existe, se puede obtener y el tamaño coincide
    CHECK(tabla.contiene(clave));
    CHECK(tabla.obtener(clave) != nullptr);
    CHECK(tabla.tam() == 1);
}


