/**
 * \file main.cpp
 * \brief Este archivo contiene la ejecuci&oacute;n principal y el men&uacute; interactivo para probar la clase ArbolB.
 * \author Dur&oacute;n Urbina, Angel Daniel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \author Rivera L&oacute;pez, Issac Abraham
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \date 21/05/2026
 * \code{.cpp}

 * \endcode
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "CapturaSegura.hpp"
#include "ArbolB.hpp"
#include "Menu.hpp"

using namespace std;

/**
 * \brief Opciones del men&uacute; principal para el &Aacute;rbol B.
 */
enum Opciones_principales {
    AGREGAR = 1,        ///< Agrega un nuevo valor al &aacute;rbol B actual.
    ELIMINAR,           ///< Elimina un valor espec&iacute;fico del &aacute;rbol B actual.
    BUSCAR,             ///< Busca si existe un elemento dentro de la estructura.
    NUMCLAVES,          ///< Muestra el n&uacute;mero total de claves en el &aacute;rbol.
    ALTURA,             ///< Calcula y muestra la altura actual del &aacute;rbol B.
    GRADO,              ///< Muestra el grado (M) del &aacute;rbol.
    ESTAVACIA,          ///< Indica si el &aacute;rbol B actual no tiene elementos.
    VACIAR,             ///< Elimina todos los elementos del &aacute;rbol B actual.
    IMPRIMIR,           ///< Imprime los elementos en orden ascendente.
    IMPRIMIRNIV,        ///< Imprime los elementos agrup&aacute;ndolos por niveles.
    IMPRIMIRARBOL,      ///< Imprime los elementos simulando la estructura de un &aacute;rbol acostado.
    DATARANDOM,         ///< Inserta un conjunto de datos aleatorios para pruebas r&aacute;pidas.
    PRUEBAS,            ///< Ejecuta la secci&oacute;n dedicada a rutinas de prueba.
    SALIR               ///< Termina la ejecuci&oacute;n del programa.
};

/** \brief Funci&oacute;n principal que ejecuta el men&uacute; interactivo del programa.
 * \return Un n&uacute;mero entero que indica el estado de terminaci&oacute;n del programa (0 si fue exitoso).
 */
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

    cout << "Grado v\240lido!" << endl;

    pausar();
    limpiarPantalla();

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
        cout << "\t" << ALTURA << ") Obtener la altura del \240rbol." << endl;
        cout << "\t" << GRADO << ") Obtener el grado del \240rbol." << endl;
        cout << "\t" << ESTAVACIA << ") Saber si el \240rbol est\240 vac\241o." << endl;
        cout << "\t" << VACIAR << ") Vaciar el \240rbol." << endl;
        cout << "\t" << IMPRIMIR << ") Imprimir (en orden)." << endl;
        cout << "\t" << IMPRIMIRNIV << ") Imprimir (como \240rbol)." << endl;
        cout << "\t" << IMPRIMIRARBOL << ") Imprimir (como \240rbol acostado)." << endl;
        cout << "\t" << DATARANDOM << ") Agregar datos aleatorios." << endl;
        cout << "\t" << PRUEBAS << ") \265rea de pruebas." << endl;
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

                case PRUEBAS:
                    areaPruebas();
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
        pausar();
        limpiarPantalla();
    }while(opcion != SALIR);

    cout << "\nEl programa ha terminado." << endl;

    system("pause");
    return 0;
}
