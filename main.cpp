#include <iostream>
#include "ArbolB.hpp"
#include "Menu.hpp"
using namespace std;

int main() {
    try {
        // Creamos un Arbol B de grado 5 (Max 4 claves por nodo, minimo 2)
        ArbolB<int, 5> arbol;

        cout << "=======================================" << endl;
        cout << "      PRUEBAS: ARBOL B (GRADO 5)       " << endl;
        cout << "=======================================" << endl << endl;

        cout << "1. Llenando el Arbol con numeros aleatorios..." << endl;


        defDatosAleatorios(arbol, 30);

        cout << "\n2. Estado del Arbol despues de las inserciones:" << endl;
        cout << "Numero total de claves: " << arbol.ObtenerNumClaves() << endl;
        cout << "Altura del arbol: " << arbol.ObtenerAltura() << endl;

        cout << "\n3. Impresion por niveles (Estructura interna):" << endl;
        arbol.ImprimirPorNiveles();

        cout << "\n4. Impresion como Arbol (Acostado):" << endl;
        cout << arbol; // Probando el operator<< sobrecargado

        cout << "\n5. Pruebas de Busqueda:" << endl;
        cout << "Buscando el 6: " << (arbol.Buscar(6) ? "Encontrado" : "No encontrado") << endl;
        cout << "Buscando el 99: " << (arbol.Buscar(99) ? "Encontrado" : "No encontrado") << endl;

    } catch (const exception& e) {
        cerr << "\nError atrapado: " << e.what() << endl;
    }

    cout << "\n--- Pruebas de insercion finalizadas ---" << endl;
    return 0;
}
