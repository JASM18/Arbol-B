#include <iostream>

#include "CapturaSegura.hpp"
#include "ArbolB.hpp"

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
    SALIR               ///< Termina el programa.
};

int main()
{
    int opcion = -1;
    int gradoUsuario = 0;

    do{
        CapturarNumero(opcion, "Grado del nodo: ");
    }while(gradoUsuario < 3);


    ArbolB<int> arbolitoB (gradoUsuario);

    int valor;

    system("pause");

    do{
        cout << "==================================" << endl;
        cout << "Proyecto final: Arbol B" << endl;
        cout << "==================================" << endl << endl;

        cout << "--- ARBOL(" << gradoUsuario << ") ACTUAL ---" << endl;
        cout << arbolitoB << endl;
        cout << "------------------------" << endl << endl;

        cout << "Opciones:" << endl;
        cout << "\t" << AGREGAR << ") Agregar un valor." << endl;
        cout << "\t" << ELIMINAR << ") Eliminar la ra\241z." << endl;
        cout << "\t" << BUSCAR << ") Buscar un elemento." << endl;
        cout << "\t" << NUMCLAVES << ") Obtener el n\243mero de claves totales." << endl;
        cout << "\t" << ALTURA << ") Obtener la altura del arbol." << endl;
        cout << "\t" << GRADO << ") Obtener el grado del arbol." << endl;
        cout << "\t" << ESTAVACIA << ") Saber si el arbol est\240 vac\241o." << endl;
        cout << "\t" << VACIAR << ") Vaciar elarbol." << endl;
        cout << "\t" << IMPRIMIR << ") Imprimir (en orden) (NO ESTA LISTA)." << endl;
        cout << "\t" << IMPRIMIRNIV << ") Imprimir (como arbol)." << endl;
        cout << "\t" << IMPRIMIRARBOL << ") Imprimir (como arbol acostado)." << endl;
        cout << "\t" << SALIR << ") Salir del programa." << endl;

        do{
            CapturarNumero(opcion, "Elige una opci\242n: ");
        }while(opcion > SALIR || opcion < AGREGAR);

        if(opcion == SALIR) continue;

        try{
            cout << "- - - - -" << endl;
            switch(opcion){

                case AGREGAR:
                    CapturarNumero(valor, "Valor a agregar: ");
                    arbolitoB.Agregar(valor);
                    cout << "Valor agregado correctamente." << endl;
                break;

                case ELIMINAR:
                    CapturarNumero(valor, "Valor a eliminar: ");

                    if(arbolitoB.Eliminar(valor)){
                        cout << "Se elimin\242 el valor " << valor << " del arbol." << endl;
                    }else{
                        cout << "[:(] El valor " << valor << " no se encontro en el arbol." << endl;
                    }

                break;

                case BUSCAR:
                    CapturarNumero(valor, "Valor a buscar: ");
                    cout << "El valor " << valor << (arbolitoB.Buscar(6) ? " SI se encontro." : " NO encontro.") << endl;
                break;

                case NUMCLAVES:
                    cout << "El arbol tiene " << arbolitoB.ObtenerNumClaves() << " claves en total." << endl;
                break;

                case ALTURA:
                    cout << "El arbol tiene altura " << arbolitoB.ObtenerNumClaves() << "." << endl;
                break;

                case GRADO:
                    cout << "El arbol es de grado " << arbolitoB.ObtenerGrado() << "." << endl;
                break;

                case ESTAVACIA:
                    if(arbolitoB.EstaVacia()){
                        cout << "El arbol S\326 est\240 vac\241o." << endl;
                    }else{
                        cout << "El arbol NO est\240 vac\241o." << endl;
                    }
                break;

                case VACIAR:
                    arbolitoB.Vaciar();
                    cout << "El arbol ha sido vaciado por completo." << endl;
                break;

                case IMPRIMIR:
                    arbolitoB.ImprimirOrden();
                break;

                case IMPRIMIRNIV:
                    arbolitoB.ImprimirPorNiveles();
                break;

                case IMPRIMIRARBOL:
                    arbolitoB.ImprimirComoArbol();
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
