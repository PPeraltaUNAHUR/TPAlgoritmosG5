#pragma once
#include <vector>
#include <functional>
#include <utility>
#include <stdexcept>

template <typename K, typename V, typename Compare = std::less<K>>
class ABB {
private:
    struct Nodo {
        K clave;
        V valor;
        Nodo* izquierdo;
        Nodo* derecho;

        Nodo(const K& c, const V& v)
            : clave(c), valor(v), izquierdo(nullptr), derecho(nullptr) {}
    };

    Nodo* raiz;
    Compare comparar;

    void destruir(Nodo* nodo) {
        if (!nodo) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

    Nodo* insertarRec(Nodo* nodo, const K& clave, const V& valor) {
        if (!nodo) {
            return new Nodo(clave, valor);
        }

        if (comparar(clave, nodo->clave)) {
            nodo->izquierdo = insertarRec(nodo->izquierdo, clave, valor);
        } else if (comparar(nodo->clave, clave)) {
            nodo->derecho = insertarRec(nodo->derecho, clave, valor);
        } else {
            nodo->valor = valor; // actualizar
        }
        return nodo;
    }

    V* buscarRec(Nodo* nodo, const K& clave) {
        if (!nodo) return nullptr;
        if (comparar(clave, nodo->clave)) return buscarRec(nodo->izquierdo, clave);
        if (comparar(nodo->clave, clave)) return buscarRec(nodo->derecho, clave);
        return &nodo->valor;
    }

    const V* buscarRec(const Nodo* nodo, const K& clave) const {
        if (!nodo) return nullptr;
        if (comparar(clave, nodo->clave)) return buscarRec(nodo->izquierdo, clave);
        if (comparar(nodo->clave, clave)) return buscarRec(nodo->derecho, clave);
        return &nodo->valor;
    }

    void rangoRec(const Nodo* nodo, const K& desde, const K& hasta, std::vector<V>& resultado) const {
        if (!nodo) return;

        if (comparar(desde, nodo->clave)) {
            rangoRec(nodo->izquierdo, desde, hasta, resultado);
        }

        if (!comparar(nodo->clave, desde) && !comparar(hasta, nodo->clave)) {
            resultado.push_back(nodo->valor);
        }

        if (comparar(nodo->clave, hasta)) {
            rangoRec(nodo->derecho, desde, hasta, resultado);
        }
    }

    void enOrdenRec(const Nodo* nodo, std::vector<std::pair<K, V>>& resultado) const {
        if (!nodo) return;
        enOrdenRec(nodo->izquierdo, resultado);
        resultado.emplace_back(nodo->clave, nodo->valor);
        enOrdenRec(nodo->derecho, resultado);
    }

public:
    ABB() : raiz(nullptr), comparar(Compare()) {}
    explicit ABB(Compare comp) : raiz(nullptr), comparar(comp) {}
    ~ABB() {
        destruir(raiz);
    }

    void insertar(const K& clave, const V& valor) {
        raiz = insertarRec(raiz, clave, valor);
    }

    V* buscar(const K& clave) {
        return buscarRec(raiz, clave);
    }

    const V* buscar(const K& clave) const {
        return buscarRec(raiz, clave);
    }

    std::vector<V> rango(const K& desde, const K& hasta) const {
        std::vector<V> resultado;
        rangoRec(raiz, desde, hasta, resultado);
        return resultado;
    }

    bool vacio() const {
        return raiz == nullptr;
    }

    std::vector<std::pair<K, V>> entradas() const {
        std::vector<std::pair<K, V>> resultado;
        enOrdenRec(raiz, resultado);
        return resultado;
    }
};
