# TPAlgoritmosG5
TP Algoritmo Grupo 5

# Plataforma logística
Sistema de gestión de centros, envíos y optimización de carga para el TP de Algoritmos.

## Requisitos
- g++ ≥ C++17
- make

## Comandos principales

```bash
# Compilar la aplicación CLI
make            # o make app

# Ejecutarla (utiliza build/app)
make run

# Construir y ejecutar la suite de tests
make test
```

Los binarios se generan en `build/app` y `build/tests_hash`. Para filtrar tests puedes pasar flags directos:

```bash
./build/tests_hash -tc="Grafo"
```

## Uso de la aplicación
Los archivos de datos por defecto son los provistos en `src/data/`. Una vez compilada la app:

```bash
./build/app
```

El menú principal ofrece:

1. Listados de centros por envíos, capacidad o empleados.
2. Cálculo de camino mínimo entre dos centros vía Dijkstra.
3. Consultas de envíos en un rango de fechas, detección de sobrecargas semanales y búsqueda por ID de paquete.
4. Optimización de carga (punto C) usando backtracking.
5. Alta y baja manual de centros durante la ejecución.

Todas las entradas numéricas se validan y el sistema informa si el centro solicitado no existe.

## Estructuras y decisiones algorítmicas
- **TablaHash**: implementación propia con hashing polinómico base 31 mod 1e9+9, elegida por su buen comportamiento distributivo para cadenas cortas (códigos de centro) y baja tasa de colisión. Se usa para indexar centros y los diccionarios secundarios de envíos.
- **ABB (árbol binario de búsqueda)**: almacena los envíos por centro ordenados por fecha, permitiendo consultas por rango en O(log n + k).
- **Cola de prioridad**: heap binario personalizado que sirve como cola mínima en Dijkstra.
- **Grafo**: representado como hash de listas de adyacencia para permitir crecimiento dinámico de la red.
- **Backtracking**: explora todas las combinaciones de paquetes preservando el mejor valor sin superar la capacidad del camión; los tests cubren el caso óptimo.

La documentación y justificación de estas elecciones forma parte de la defensa del TP.
