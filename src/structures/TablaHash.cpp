// Implementación de la función hash polinómica optimizada para strings
#include <string>

std::size_t hashString(const std::string& clave, std::size_t capacidad) {
    const long long primoBase = 31;                // p
    const long long primoGrandeMod = 1000000009LL; // m = 1e9 + 9
    long long hashRodante = 0;
    long long potenciaBase = 1;

    for (char caracter : clave) {
        long long valorCaracter = static_cast<unsigned char>(caracter);
        hashRodante = (hashRodante + (valorCaracter + 1) * potenciaBase) % primoGrandeMod;
        potenciaBase = (potenciaBase * primoBase) % primoGrandeMod;
    }
    return static_cast<std::size_t>(hashRodante % static_cast<long long>(capacidad));
}


