# TPAlgoritmosG5
TP Algoritmo Grupo 5

## Ejecución de tests (doctest)

Este proyecto usa [doctest](https://github.com/doctest/doctest) como framework de testing (header-only) y un Makefile para simplificar la compilación/ejecución.

### Requisitos
- g++ con soporte C++17

### Comandos principales

Desde la raíz del proyecto:

```bash
make test
```

Esto compila y ejecuta los tests, generando el binario en `build/tests_hash`.

Otros comandos útiles:

```bash
# Solo compilar (sin ejecutar)
make build

# Limpiar artefactos de compilación
make clean
```

### Filtrar tests / opciones avanzadas

Puedes pasar opciones directamente al binario de tests generado por doctest. Por ejemplo, para ejecutar solo un caso cuyo nombre contenga "Eliminación":

```bash
./build/tests_hash -tc="Eliminación"
```

Ver ayuda completa de doctest:

```bash
./build/tests_hash -h
```

