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

Dataset inicial (`centros.txt`) incluye los códigos `BUE`, `CBA`, `MZA`, `ROS`, `SAL` y `NEU`, por lo que puedes usar cualquiera de ellos en las consultas de la CLI.

El menú principal ofrece:

1. Listados de centros por envíos, capacidad o empleados.
2. Cálculo de camino mínimo entre dos centros vía Dijkstra.
3. Consultas de envíos en un rango de fechas, detección de sobrecargas semanales y búsqueda por ID de paquete.
4. Optimización de carga (punto C) usando backtracking.
5. Alta y baja manual de centros durante la ejecución.
6. Carga incremental de centros desde archivos externos ubicados en `src/data/imports/`.

Todas las entradas numéricas se validan y el sistema informa si el centro solicitado no existe.

### Guión sugerido para la demo

1. **Mostrar la red inicial**  
   - Opción `1` para listar centros; explicar que provienen de `centros.txt`.  
   - Opción `4` con `CBA` → `MZA` para mostrar el camino mínimo y distancia agregada.

2. **Analizar envíos reales**  
   - Opción `5` sobre `BUE` con rango `20250101`–`20250107` (o el que corresponda) para ver cómo se consulta el ABB.  
   - Opción `6` con umbral `2` para que aparezca un centro sobrecargado.  
   - Opción `7` con el paquete `1002` para ilustrar la búsqueda hash.

3. **Optimización (punto C)**  
   - Opción `8`, ingresar capacidad `12` y mostrar la lista de IDs seleccionados por el backtracking.

4. **CRUD y carga adicional**  
   - Opción `9` para crear un centro nuevo (ej. `ROS`).  
   - Opción `2` u `3` para confirmar el orden según el criterio.  
   - Opción `10` para eliminarlo.  
    - Opción `11` para mostrar todos los archivos dentro de `src/data/imports/`, elegir uno (ej. `centros_demo.txt`) y cargarlo sin reiniciar la app. También permite trabajar con archivos personalizados que se copien en ese directorio.

## Estructuras y decisiones algorítmicas
- **TablaHash**: implementación propia con hashing polinómico base 31 mod 1e9+9, elegida por su buen comportamiento distributivo para cadenas cortas (códigos de centro) y baja tasa de colisión. Se usa para indexar centros y los diccionarios secundarios de envíos.
- **ABB (árbol binario de búsqueda)**: almacena los envíos por centro ordenados por fecha, permitiendo consultas por rango en O(log n + k).
- **Cola de prioridad**: heap binario personalizado que sirve como cola mínima en Dijkstra.
- **Grafo**: representado como hash de listas de adyacencia para permitir crecimiento dinámico de la red.
- **Backtracking**: explora todas las combinaciones de paquetes preservando el mejor valor sin superar la capacidad del camión; los tests cubren el caso óptimo. La complejidad temporal es de O(2^n) con n siendo el numero de paquetes. 

La documentación y justificación de estas elecciones forma parte de la defensa del TP.
