#pragma once
#include <vector>
#include <stdexcept>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class ColaPrioridad {
private:
    std::vector<T> elementos;
    Compare comparar;

    void siftUp(std::size_t idx) {
        while (idx > 0) {
            std::size_t padre = (idx - 1) / 2;
            if (!comparar(elementos[idx], elementos[padre])) {
                break;
            }
            std::swap(elementos[idx], elementos[padre]);
            idx = padre;
        }
    }

    void siftDown(std::size_t idx) {
        const std::size_t n = elementos.size();
        while (true) {
            std::size_t izquierdo = 2 * idx + 1;
            std::size_t derecho = 2 * idx + 2;
            std::size_t menor = idx;

            if (izquierdo < n && comparar(elementos[izquierdo], elementos[menor])) {
                menor = izquierdo;
            }
            if (derecho < n && comparar(elementos[derecho], elementos[menor])) {
                menor = derecho;
            }

            if (menor == idx) {
                break;
            }

            std::swap(elementos[idx], elementos[menor]);
            idx = menor;
        }
    }

public:
    ColaPrioridad() = default;
    explicit ColaPrioridad(Compare comp) : elementos(), comparar(comp) {}

    bool vacia() const {
        return elementos.empty();
    }

    const T& primero() const {
        if (vacia()) {
            throw std::out_of_range("ColaPrioridad::primero - vacia");
        }
        return elementos.front();
    }

    void insertar(const T& elemento) {
        elementos.push_back(elemento);
        siftUp(elementos.size() - 1);
    }

    T extraer() {
        if (vacia()) {
            throw std::out_of_range("ColaPrioridad::extraer - vacia");
        }
        T resultado = elementos.front();
        elementos[0] = elementos.back();
        elementos.pop_back();
        if (!elementos.empty()) {
            siftDown(0);
        }
        return resultado;
    }

    std::size_t tam() const {
        return elementos.size();
    }
};
