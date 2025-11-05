#pragma once
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <type_traits>

std::size_t hashString(const std::string& clave, std::size_t capacidad);

template <typename K, typename V>
class TablaHash {
private:
    std::vector<std::list<std::pair<K, V>>> cubetas;
    std::size_t capacidad;
    std::size_t cantidadElementos;

    // Calcula índice de bucket para una clave
    std::size_t calcularIndiceCubeta(const K& clave) const {
        if constexpr (std::is_same<K, std::string>::value) {
            return hashString(clave, capacidad);
        } else {
            std::size_t valorHash = std::hash<K>{}(clave);
            return valorHash % capacidad;
        }
    }

    // Rehash opcional cuando el factor de carga supera el umbral
    void redistribuirSiEsNecesario() {
        const double factorCarga = static_cast<double>(cantidadElementos) / static_cast<double>(capacidad);
        if (factorCarga > 0.75) {
            redistribuir(capacidad * 2 + 1); // crecer y mantener impar
        }
    }

    void redistribuir(std::size_t nuevaCapacidad) {
        std::vector<std::list<std::pair<K, V>>> nuevasCubetas(nuevaCapacidad);
        for (const auto& cubeta : cubetas) {
            for (const auto& entrada : cubeta) {
                const std::size_t nuevoIndice = [&]() {
                    if constexpr (std::is_same<K, std::string>::value) {
                        return hashString(entrada.first, nuevaCapacidad);
                    } else {
                        return std::hash<K>{}(entrada.first) % nuevaCapacidad;
                    }
                }();
                nuevasCubetas[nuevoIndice].push_back(entrada);
            }
        }
        cubetas.swap(nuevasCubetas);
        capacidad = nuevaCapacidad;
    }

public:
    explicit TablaHash(std::size_t cap = 101)
        : cubetas(cap), capacidad(cap), cantidadElementos(0) {}

    void insertar(const K& clave, const V& valor) {
        const std::size_t indiceCubeta = calcularIndiceCubeta(clave);
        for (auto& entrada : cubetas[indiceCubeta]) {
            if (entrada.first == clave) {
                entrada.second = valor; // actualizar
                return;
            }
        }
        cubetas[indiceCubeta].push_back(std::make_pair(clave, valor));
        ++cantidadElementos;
        redistribuirSiEsNecesario();
    }

    bool contiene(const K& clave) const {
        const std::size_t indiceCubeta = calcularIndiceCubeta(clave);
        for (const auto& entrada : cubetas[indiceCubeta]) {
            if (entrada.first == clave) return true;
        }
        return false;
    }

    V* obtener(const K& clave) {
        const std::size_t indiceCubeta = calcularIndiceCubeta(clave);
        for (auto& entrada : cubetas[indiceCubeta]) {
            if (entrada.first == clave) return &entrada.second;
        }
        return nullptr;
    }

    void eliminar(const K& clave) {
        const std::size_t indiceCubeta = calcularIndiceCubeta(clave);
        for (auto it = cubetas[indiceCubeta].begin(); it != cubetas[indiceCubeta].end(); ++it) {
            if (it->first == clave) {
                cubetas[indiceCubeta].erase(it);
                --cantidadElementos;
                return;
            }
        }
    }

    std::size_t tam() const {
        return cantidadElementos;
    }

    double factor_carga() const {
        return static_cast<double>(cantidadElementos) / static_cast<double>(capacidad);
    }
};