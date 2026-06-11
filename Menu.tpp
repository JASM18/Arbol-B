/**
 * \file Menu.tpp
 * \brief Implementaci&oacute;n de las funciones del men&uacute; y pruebas para el &Aacute;rbol B.
 * \author Dur&oacute;n Urbina, Angel Daniel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \author Rivera L&oacute;pez, Issac Abraham
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \date 27/05/2026
 */

#include <iostream>
#include <sstream>

#include "CapturaSegura.hpp"
#include "Aleatorio.hpp"

using std::cout;
using std::endl;

//***********************************************

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");   // para windows
#else
    system("clear"); // para linux
#endif
}

//***********************************************

void pausar()
{
    cout << "Presione Enter para continuar...";

    // se limpia el buffer
    if(std::cin.peek() == '\n'){
        std::cin.ignore();
    }

    // pausa la ejecucion hasta que se presione Enter
    std::cin.get();
}

//***********************************************

template<typename T>
void GAgregar(ArbolB<T> &arbol)
{
    T valor;
    CapturarNumero(valor, "Valor a agregar: ");
    arbol.Agregar(valor);

    std::cout << "Valor agregado correctamente." << std::endl;
}

//***********************************************

template<typename T>
void GEliminar(ArbolB<T> &arbol)
{
    T valor;
    CapturarNumero(valor, "Valor a eliminar: ");

    if(arbol.Eliminar(valor)){
        std::cout << "Se elimin\242 el valor " << valor << " del \240rbol." << std::endl;
    }else{
        std::cout << "[:(] El valor " << valor << " no se encontr\242 en el \240rbol." << std::endl;
    }
}

//***********************************************

template<typename T>
void GBuscar(const ArbolB<T> &arbol)
{
    T valor;
    CapturarNumero(valor, "Valor a buscar: ");
    if(arbol.Buscar(valor)){
        std::cout << "El valor " << valor << " S\326 se encontr\242." << std::endl;
    }else{
        std::cout << "El valor " << valor << " NO se encontr\242." << std::endl;
    }
}

//***********************************************

template<typename T>
void GNumClaves(const ArbolB<T> &arbol)
{
    std::cout << "El \240rbol tiene " << arbol.ObtenerNumClaves() << " claves en total." << std::endl;
}

//***********************************************

template<typename T>
void GAltura(const ArbolB<T> &arbol)
{
    std::cout << "El \240rbol tiene altura " << arbol.ObtenerAltura() << "." << std::endl;
}

//***********************************************

template<typename T>
void GGrado(const ArbolB<T> &arbol)
{
    std::cout << "El \240rbol es de grado " << arbol.ObtenerGrado() << "." << std::endl;
}

//***********************************************

template<typename T>
void GEstaVacia(const ArbolB<T> &arbol)
{
    if(arbol.EstaVacia()){
        std::cout << "El \240rbol S\326 est\240 vac\241o." << std::endl;
    }else{
        std::cout << "El \240rbol NO est\240 vac\241o." << std::endl;
    }
}

//***********************************************

template<typename T>
void GVaciar(ArbolB<T> &arbol)
{
    if(arbol.EstaVacia()){
        std::cout << "El \240rbol ya estaba vac\241o." << std::endl;
    }else{
        arbol.Vaciar();
        std::cout << "El \240rbol ha sido vaciado por completo." << std::endl;
    }
}

//***********************************************

template<typename T>
void GImprimirOrden(const ArbolB<T> &arbol)
{
    std::cout << "En orden ascendente: ";
    arbol.ImprimirOrden();
    std::cout << std::endl;
}

//***********************************************

template<typename T>
void GImprimirPorNiveles(const ArbolB<T> &arbol)
{
    std::cout << "Por niveles:" << std::endl;
    arbol.ImprimirPorNiveles();
}

//***********************************************

template<typename T>
void GImprimirComoArbol(const ArbolB<T> &arbol)
{
    std::cout << "Estructura del \240rbol:";
    arbol.ImprimirComoArbol();
}

//***********************************************

template <typename T>
void defDatosAleatorios(ArbolB<T>& arbolito)
{
    int numDatos;

    do{
        CapturarNumero(numDatos, "N\243mero de datos a ingresar: ");
    }while(numDatos < 1);

    int inicio = 1;
    int fin = 1000;

    for(int i = 0 ; i < numDatos ; ++i){

        T valorAleatorio = static_cast<T>(aleatorio(inicio, fin));

        arbolito.Agregar(valorAleatorio);
    }
    std::cout << "\255Datos agregados exitosamente!" << std::endl;
}

//***********************************************

void areaPruebas()
{
    cout << "==================================" << endl;
    cout << "\265rbol B (\265rea de pruebas)" << endl;
    cout << "==================================" << endl << endl;

    // ---------------------------------------------------------
    // Prueba 1: División básica
    // ---------------------------------------------------------
    ArbolB<int> arbolPrueba(3); // Grado 3 (Max 2 claves por nodo)

    cout << "-> Probando la divisi\242n (Grado 3)..." << endl;
    cout << "Insertando: 10, 15, 30" << endl;
    arbolPrueba.Agregar(10);
    arbolPrueba.Agregar(15);
    // Al agregar el 30, el nodo supera las 2 claves permitidas y se divide
    arbolPrueba.Agregar(30);

    arbolPrueba.ImprimirPorNiveles();
    cout << "Altura actual: " << arbolPrueba.ObtenerAltura() << endl << endl;

    // ---------------------------------------------------------
    // Prueba 2: Desbordamiento Central (Sandwich)
    // ---------------------------------------------------------
    ArbolB<int> arbolSandwich(5);

    cout << "-> Probando desbordamiento central (Grado 5)..." << endl;
    cout << "Insertando valores alternados: 10, 100, 20, 90, 30, 80, 40, 70, 50, 60" << endl;

    int arr[] = {10, 100, 20, 90, 30, 80, 40, 70, 50, 60};
    for(int i = 0; i < 10; i++) {
        arbolSandwich.Agregar(arr[i]);
    }

    arbolSandwich.ImprimirPorNiveles();
    cout << endl;

    // ---------------------------------------------------------
    // Prueba 3: Manejo de Clones (Duplicados)
    // ---------------------------------------------------------
    ArbolB<int> arbolClones(5);

    cout << "-> Probando inserci\242n de clones / duplicados (Grado 5)..." << endl;
    cout << "Insertando ocho veces el numero 42:" << endl;

    for(int i = 0; i < 8; i++) {
        arbolClones.Agregar(42);
    }

    arbolClones.ImprimirPorNiveles();
    cout << endl;

    // ---------------------------------------------------------
    // Prueba 4: Plantillas con Caracteres ASCII
    // ---------------------------------------------------------
    ArbolB<char> arbolChar(5);

    cout << "-> Probando el uso de templates con caracteres (Grado 5)..." << endl;
    cout << "Insertando la palabra desordenada: B, A, L, A, T, R, O" << endl;

    char palabra[] = {'B', 'A', 'L', 'A', 'T', 'R', 'O'};
    for(int i = 0; i < 7; i++) {
        arbolChar.Agregar(palabra[i]);
    }

    arbolChar.ImprimirPorNiveles();
    cout << "Impresi\242n InOrden (verificando orden alfab\202tico): ";
    arbolChar.ImprimirOrden();
}
