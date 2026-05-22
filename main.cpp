#include <iostream>

#include "ArbolB.hpp"

using namespace std;

int main()
{
    ArbolB<int, -3> arbolito;

    cout << "Hola prueba: " << arbolito.ObtenerGrado() << endl;

    /*
    cout << arbolito;

    arbolito.Agregar(10);

    cout << arbolito;

    for(int i = 1 ; i < 10 ; ++i){
        cout << "========" << endl;
        arbolito.Agregar(i);
        cout << arbolito << endl;
    }
    */
    return 0;
}
