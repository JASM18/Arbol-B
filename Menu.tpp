#include <iostream>
#include <cstdlib>  // srand(), rand()
#include <ctime>    // time(), clock()

// =============================================================================
//  CONTROL DE SEMILLA
//  Comenta el #define  -> semilla distinta cada ejecucion.
//  Déjalo activo       -> semilla fija (misma secuencia siempre).
//  Cambia el número para obtener otra secuencia fija diferente.
// =============================================================================
// #define SEMILLA_FIJA 42
// =============================================================================

// El rango se calcula como [1, numDatos * 10]:
//   numDatos = 10  ->  rango [1, 100]
//   numDatos = 50  ->  rango [1, 500]
//   numDatos = 100 ->  rango [1, 1000]
template<typename T, int Mgrado>
void defDatosAleatorios(ArbolB<T, Mgrado>& arbolito, int numDatos)
{
    T min_val = static_cast<T>(1);
    T max_val = static_cast<T>(numDatos * 10);

#ifdef SEMILLA_FIJA
    srand(SEMILLA_FIJA);
    std::cout << "[semilla fija: " << SEMILLA_FIJA << "]\n";
#else
    // time() cambia cada segundo, clock() cambia cada llamada al programa.
    // El XOR de ambos garantiza semillas distintas aunque corran en el mismo segundo.
    unsigned int semilla = static_cast<unsigned int>(time(nullptr))
                         ^ static_cast<unsigned int>(clock());
    srand(semilla);
    std::cout << "[semilla aleatoria: " << semilla << "]\n";
#endif

    std::cout << "--- Generando " << numDatos
              << " numeros en el rango ["
              << min_val << ", " << max_val << "] ---" << std::endl;

    int rango      = static_cast<int>(max_val - min_val + 1);
    int insertados = 0;
    int duplicados = 0;

    for (int i = 0; i < numDatos; ++i) {
        T numero = static_cast<T>(rand() % rango + static_cast<int>(min_val));

        if (arbolito.Agregar(numero)) {
            std::cout << numero << " ";
            ++insertados;
        } else {
            std::cout << "[" << numero << " dup] ";
            ++duplicados;
        }
    }

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Exitosos:             " << insertados      << std::endl;
    std::cout << "Duplicados ignorados: " << duplicados      << std::endl;
    std::cout << "----------------------------------------\n" << std::endl;
}
