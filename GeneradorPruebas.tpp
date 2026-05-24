#include <iostream>
#include <random>

template<typename T, int Mgrado>
void LlenarArbolAleatorio(ArbolB<T, Mgrado>& arbol, int cantidad, T min_val, T max_val) 
{
    // Configuración moderna del generador de números aleatorios en C++
    std::random_device rd;  // Semilla aleatoria del hardware
    std::mt19937 gen(rd()); // Generador Mersenne Twister
    std::uniform_int_distribution<T> distrib(min_val, max_val); // Distribución uniforme

    std::cout << "--- Generando " << cantidad << " numeros aleatorios ---" << std::endl;
    int insertados = 0;
    int duplicados = 0;

    for (int i = 0; i < cantidad; ++i) {
        T numero_aleatorio = distrib(gen);
        
        // Intentamos agregar el número al árbol
        if (arbol.Agregar(numero_aleatorio)) {
            std::cout << numero_aleatorio << " ";
            insertados++;
        } else {
            // El método Agregar retorna false si la clave ya existe
            std::cout << "[" << numero_aleatorio << " dup] ";
            duplicados++;
        }
    }
    
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Resumen de insercion:" << std::endl;
    std::cout << "- Exitosos: " << insertados << std::endl;
    std::cout << "- Duplicados ignorados: " << duplicados << std::endl;
    std::cout << "----------------------------------------\n" << std::endl;
    return;
}
