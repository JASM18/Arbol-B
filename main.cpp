#include <iostream>
#include <ctime>

#include "ArbolB.hpp"
#include "Menu.hpp"

using namespace std;

int main()
{

    srand(time(NULL));

    try {
        // Creamos un Arbol B de grado 5 (Max 4 claves por nodo, minimo 2)
        ArbolB<int, 5> arbol;

        cout << "=======================================" << endl;
        cout << "      PRUEBAS: ARBOL B (GRADO 5)       " << endl;
        cout << "=======================================" << endl << endl;

        cout << "1. Llenando el Arbol con n\243meros aleatorios..." << endl;

        defDatosAleatorios(arbol, 30);

        cout << "\n2. Estado del Arbol despues de las inserciones:" << endl;
        cout << "N\243mero total de claves: " << arbol.ObtenerNumClaves() << endl;
        cout << "Altura del \240rbol: " << arbol.ObtenerAltura() << endl;

        cout << "\n3. Impresi\242n por niveles (Estructura interna):" << endl;
        arbol.ImprimirPorNiveles();

        cout << "\n4. Impresi\242n como Arbol (Acostado):" << endl;
        cout << arbol; // Probando el operator<< sobrecargado

        cout << "\n5. Pruebas de B\243squeda:" << endl;
        cout << "Buscando el 6: " << (arbol.Buscar(6) ? "Encontrado" : "No encontrado") << endl;
        cout << "Buscando el 99: " << (arbol.Buscar(99) ? "Encontrado" : "No encontrado") << endl;


        cout << "\n6. Pruebas de eliminaci\242n de elementos del \240rbol:" << endl;
        cout << "Eliminaci\242n del n\243mero 5: " << (arbol.Eliminar(5)? "Se ha eliminado el 5": "No se ha encontrado en el \240rbol")   << endl;
        cout << "Eliminaci\242n del n\243mero 12: "<< (arbol.Eliminar(12)? "Se ha eliminado el 12": "No se ha encontrado en el \240rbol") << endl;
        cout << "Eliminaci\242n del n\243mero 67: "<< (arbol.Eliminar(67)? "Se ha eliminado el 67": "No se ha encontrado en el \240rbol") << endl;


        cout << "Imprimiendo de nuevo el \240rbol para visualizar las eliminaciones" << endl;
        cout << "Impresi\242n por niveles (Estructura interna):" << endl;
        arbol.ImprimirPorNiveles();
        cout << "Impresi\242n como Arbol (Acostado):" << endl;
        cout << arbol;


    } catch (const exception& e) {
        cerr << "\nError atrapado: " << e.what() << endl;
    }

    cout << "\nSe acavoid" << endl;
    return 0;
}
