#include <iostream>

#include "CapturaSegura.hpp"
#include "Aleatorio.hpp"

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
        std::cout << "Se elimin\242 el valor " << valor << " del arbol." << std::endl;
    }else{
        std::cout << "[:(] El valor " << valor << " no se encontr\242 en el arbol." << std::endl;
    }
}

//***********************************************

template<typename T>
void GBuscar(const ArbolB<T> &arbol)
{
    T valor;
    CapturarNumero(valor, "Valor a buscar: ");
    if(arbol.Buscar(valor)){
        std::cout << "El valor " << valor << " S\326 se encontro." << std::endl;
    }else{
        std::cout << "El valor " << valor << " NO se encontro." << std::endl;
    }
}

//***********************************************

template<typename T>
void GNumClaves(const ArbolB<T> &arbol)
{
    std::cout << "El arbol tiene " << arbol.ObtenerNumClaves() << " claves en total." << std::endl;
}

//***********************************************

template<typename T>
void GAltura(const ArbolB<T> &arbol)
{
    std::cout << "El arbol tiene altura " << arbol.ObtenerAltura() << "." << std::endl;
}

//***********************************************

template<typename T>
void GGrado(const ArbolB<T> &arbol)
{
    std::cout << "El arbol es de grado " << arbol.ObtenerGrado() << "." << std::endl;
}

//***********************************************

template<typename T>
void GEstaVacia(const ArbolB<T> &arbol)
{
    if(arbol.EstaVacia()){
        std::cout << "El arbol S\326 est\240 vac\241o." << std::endl;
    }else{
        std::cout << "El arbol NO est\240 vac\241o." << std::endl;
    }
}

//***********************************************

template<typename T>
void GVaciar(ArbolB<T> &arbol)
{
    if(arbol.EstaVacia()){
        std::cout << "El arbol ya estaba vacio." << std::endl;
    }else{
        arbol.Vaciar();
        std::cout << "El arbol ha sido vaciado por completo." << std::endl;
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
    std::cout << "Estructura del arbol:";
    arbol.ImprimirComoArbol();
}

//***********************************************

template <typename T>
void defDatosAleatorios(ArbolB<T>& arbolito)
{
    int numDatos;

    do{
        CapturarNumero(numDatos, "Numero de datos a ingresar: ");
    }while(numDatos < 1);

    int inicio = 1;
    int fin = 1000;

    for(int i = 0 ; i < numDatos ; ++i){

        T valorAleatorio = static_cast<T>(aleatorio(inicio, fin));

        arbolito.Agregar(valorAleatorio);
    }
    std::cout << "Datos agregados exitosamente!" << std::endl;
}
