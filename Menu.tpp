#include "Aleatorio.hpp"

template <typename T>
void defDatosAleatorios(ArbolB<T>& arbolito, int numDatos)
{
    int inicio = 1;
    int fin = 100;

    for(int i = 0 ; i < numDatos ; ++i){

        T valorAleatorio = static_cast<T>(aleatorio(inicio, fin));

        arbolito.Agregar(valorAleatorio);
    }
}
