#include <iostream>
#include <cstdlib>
#include <ctime>

#include "CapturaSegura.hpp"
#include "ArbolB.hpp"
#include "Menu.hpp"

using namespace std;

/**
 * \brief Opciones del men&uacute; principal para el mont&iacute;culo.
 */
enum Opciones_principales {
    AGREGAR = 1,        ///< Agrega un nuevo valor al mont&iacute;culo actual.
    ELIMINAR,           ///< Elimina la ra&iacute;z del mont&iacute;culo actual.
    BUSCAR,
    NUMCLAVES,          ///< Muestra el n&uacute;mero de claves en total.
    ALTURA,
    GRADO,
    ESTAVACIA,          ///< Indica si el mont&iacute;culo actual no tiene elementos.
    VACIAR,             ///< Elimina todos los elementos del mont&iacute;culo actual.
    IMPRIMIR,           ///< Imprime los elementos en orden.
    IMPRIMIRNIV,
    IMPRIMIRARBOL,
    DATARANDOM,
    SALIR               ///< Termina el programa.
};

int main()
{
    srand((time(NULL)));

    int opcion = -1;
    int grado = 3;

    cout << "==================================" << endl;
    cout << "Proyecto final: Arbol B" << endl;
    cout << "==================================" << endl << endl;

    do{
        CapturarNumero(grado, "Grado del Arbol B: ");
    }while(grado < 3);

    cout << "Grado valido!" << endl;

    system("pause");
    system("CLS");

    ArbolB<int> arbolitoB(grado);

    do{
        cout << "==================================" << endl;
        cout << "Proyecto final: Arbol B" << endl;
        cout << "==================================" << endl << endl;

        cout << "--- Arbol B(M=" << grado << ") actual ---" << endl;
        cout << arbolitoB;
        cout << "------------------------" << endl << endl;

        cout << "Opciones:" << endl;
        cout << "\t" << AGREGAR << ") Agregar un valor." << endl;
        cout << "\t" << ELIMINAR << ") Eliminar un valor." << endl;
        cout << "\t" << BUSCAR << ") Buscar un elemento." << endl;
        cout << "\t" << NUMCLAVES << ") Obtener el n\243mero de claves totales." << endl;
        cout << "\t" << ALTURA << ") Obtener la altura del arbol." << endl;
        cout << "\t" << GRADO << ") Obtener el grado del arbol." << endl;
        cout << "\t" << ESTAVACIA << ") Saber si el arbol est\240 vac\241o." << endl;
        cout << "\t" << VACIAR << ") Vaciar elarbol." << endl;
        cout << "\t" << IMPRIMIR << ") Imprimir (en orden)." << endl;
        cout << "\t" << IMPRIMIRNIV << ") Imprimir (como arbol)." << endl;
        cout << "\t" << IMPRIMIRARBOL << ") Imprimir (como arbol acostado)." << endl;
        cout << "\t" << DATARANDOM << ") Agregar datos aleatorios." << endl;
        cout << "\t" << SALIR << ") Salir del programa." << endl;

        do{
            CapturarNumero(opcion, "Elige una opci\242n: ");
        }while(opcion > SALIR || opcion < AGREGAR);

        if(opcion == SALIR) continue;

        try{
            cout << "- - - - -" << endl;
            switch(opcion){
                case AGREGAR:
                    GAgregar(arbolitoB);
                break;

                case ELIMINAR:
                    GEliminar(arbolitoB);
                break;

                case BUSCAR:
                    GBuscar(arbolitoB);
                break;

                case NUMCLAVES:
                    GNumClaves(arbolitoB);
                break;

                case ALTURA:
                    GAltura(arbolitoB);
                break;

                case GRADO:
                    GGrado(arbolitoB);
                break;

                case ESTAVACIA:
                    GEstaVacia(arbolitoB);
                break;

                case VACIAR:
                    GVaciar(arbolitoB);
                break;

                case IMPRIMIR:
                    GImprimirOrden(arbolitoB);
                break;

                case IMPRIMIRNIV:
                    GImprimirPorNiveles(arbolitoB);
                break;

                case IMPRIMIRARBOL:
                    GImprimirComoArbol(arbolitoB);
                break;

                case DATARANDOM:
                    defDatosAleatorios(arbolitoB);
                break;
            }

        }catch(const char* mensaje){
            cerr << "Error: " << mensaje << endl;
        }catch(const exception &error){
            cerr << "Error: " << error.what() << endl;
        }catch(...){
            cerr << "El programa tuvo un error inesperado." << endl;
        }

        cout << endl;
        system ("pause");
        system("CLS");
    }while(opcion != SALIR);

    cout << "\nEl programa ha terminado." << endl;

    system("pause");
    return 0;
}
