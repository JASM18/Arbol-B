//#include <iostream>

#include "Cola.hpp"

//***********************************************
// CONSTRUCTOR DE NODO
//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::Nodo::Nodo() : numClaves(0), esHoja(true), claves(nullptr), hijos(nullptr)
{
    // Pedimos espacio para un extra: Mgrado claves y Mgrado+1 hijos,
    // aunque el maximo permitido sea Mgrado-1 y Mgrado respectivamente.
    // Ese espacio extra es para poder insertar primero y dividir despues.
    try{
        claves = new T[Mgrado];
        hijos = new Nodo*[Mgrado + 1];
    }catch(const std::bad_alloc&){
        delete[] claves;        // si claves se asigno y hijos fallo, lo limpiamos
        throw ArbolNoMemoria();
    }

    // Inicializamos todos los punteros a hijos en nullptr.
    for(int i = 0; i <= Mgrado; ++i){
        hijos[i] = nullptr;
    }
}

//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::Nodo::~Nodo()
{
    // Solo liberamos los arreglos. La destruccion recursiva la hace Podar.
    delete[] claves;
    delete[] hijos;
}

//***********************************************
// CONSTRUCTORES DEL ARBOL
//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::ArbolB() : numClaves(0), raiz(nullptr)
{
}

//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::~ArbolB()
{
    Vaciar();
}

//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::ArbolB(const ArbolB &arbol) : numClaves(0), raiz(nullptr)
{
    *this = arbol;
}

//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado> & ArbolB<T, Mgrado>::operator=(const ArbolB &arbol)
{
    if(this == &arbol) return *this;
    Vaciar();

    CopiarPorNiveles(arbol);
    return *this;
}

//***********************************************
// METODOS PUBLICOS
//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Agregar(T valor)
{
    // Caso 1: arbol vacio. Creamos la raiz con esta unica clave.
    if(raiz == nullptr){
        try{
            raiz = new Nodo();
        }catch(const std::bad_alloc&){
            throw ArbolNoMemoria();
        }
        raiz->claves[0] = valor;
        raiz->numClaves = 1;
        ++numClaves;
        return true;
    }

    // Caso 2: el arbol no esta vacio. Insertamos recursivamente.
    T clavePromovida;
    Nodo *hijoNuevo = nullptr;
    bool huboDivision = false;

    bool seAgrego = Agregar(valor, raiz, clavePromovida, hijoNuevo, huboDivision);

    // Caso 3: si la raiz se dividio durante la recursion, creamos una nueva raiz.
    // Esta es la unica forma en que un arbol B crece en altura.
    if(huboDivision){
        Nodo *nuevaRaiz;
        try{
            nuevaRaiz = new Nodo();
        }catch(const std::bad_alloc&){
            throw ArbolNoMemoria();
        }
        nuevaRaiz->esHoja = false;
        nuevaRaiz->numClaves = 1;
        nuevaRaiz->claves[0] = clavePromovida;
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->hijos[1] = hijoNuevo;
        raiz = nuevaRaiz;
    }

    if(seAgrego) ++numClaves;
    return seAgrego;
}

//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Buscar(T valor) const
{
    return Buscar(valor, raiz);
}

//***********************************************

template<typename T, int Mgrado>
int ArbolB<T, Mgrado>::ObtenerNumClaves() const
{
    return numClaves;
}

//***********************************************

template<typename T, int Mgrado>
int ArbolB<T, Mgrado>::ObtenerAltura() const
{
    return ObtenerAltura(raiz);
}

//***********************************************

template<typename T, int Mgrado>
int ArbolB<T,Mgrado>::ObtenerGrado() const
{
    return Mgrado;
}

//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::EstaVacia() const
{
    return numClaves == 0;
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::Vaciar()
{
    Podar(raiz);
    raiz = nullptr;
    numClaves = 0;
}

//***********************************************
// METODOS PRIVADOS
//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Agregar(T valor, Nodo *subRaiz, T &clavePromovida, Nodo *&hijoNuevo, bool &huboDivision)
{
    // 1) Encontrar la posicion donde iria el valor (o donde ya esta).
    int i = 0;
    while(i < subRaiz->numClaves && subRaiz->claves[i] < valor){
        ++i;
    }

    // 2) Si la clave ya existe en este nodo, no se agrega.
    if(i < subRaiz->numClaves && subRaiz->claves[i] == valor){
        huboDivision = false;
        return false;
    }

    // 3) Decision: bajar al hijo o insertar aqui mismo.
    bool seAgrego;
    if(subRaiz->esHoja){
        // Insertamos la clave en posicion i, corriendo las demas a la derecha.
        for(int j = subRaiz->numClaves; j > i; --j){
            subRaiz->claves[j] = subRaiz->claves[j - 1];
        }
        subRaiz->claves[i] = valor;
        ++subRaiz->numClaves;
        seAgrego = true;

    }else{
        // Bajamos al hijo i. Si esa recursion provoca una division, hay que
        // absorber aqui la clave promovida y el nuevo hijo.
        T clavePromHijo;
        Nodo *hijoNuevoSub = nullptr;
        bool huboDivisionSub = false;

        seAgrego = Agregar(valor, subRaiz->hijos[i], clavePromHijo, hijoNuevoSub, huboDivisionSub);

        if(huboDivisionSub){
            // Insertamos clavePromHijo en posicion i y hijoNuevoSub en posicion i+1.
            for(int j = subRaiz->numClaves; j > i; --j){
                subRaiz->claves[j] = subRaiz->claves[j - 1];
                subRaiz->hijos[j + 1] = subRaiz->hijos[j];
            }
            subRaiz->claves[i] = clavePromHijo;
            subRaiz->hijos[i + 1] = hijoNuevoSub;
            ++subRaiz->numClaves;
        }
    }

    // 4) Si tras insertar este nodo se desbordo (Mgrado claves), lo dividimos
    //    y reportamos al padre.
    if(subRaiz->numClaves == Mgrado){
        DividirNodo(subRaiz, clavePromovida, hijoNuevo);
        huboDivision = true;
    }else{
        huboDivision = false;
    }

    return seAgrego;
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::DividirNodo(Nodo *nodoLleno, T &clavePromovida, Nodo *&hijoNuevo)
{
    // El nodo tiene Mgrado claves: [0, 1, ..., Mgrado-1].
    // Indice de la clave del medio (la que sube al padre).
    int med = Mgrado / 2;

    // Crear el nuevo hermano derecho.
    Nodo *nuevoDer;
    try{
        nuevoDer = new Nodo();
    }catch(const std::bad_alloc&){
        throw ArbolNoMemoria();
    }
    nuevoDer->esHoja = nodoLleno->esHoja;

    // Copiar las claves [med+1, Mgrado-1] al nuevo nodo.
    int claveDest = 0;
    for(int i = med + 1; i < Mgrado; ++i){
        nuevoDer->claves[claveDest] = nodoLleno->claves[i];
        ++claveDest;
    }
    nuevoDer->numClaves = claveDest;

    // Si no es hoja, copiar tambien los hijos [med+1, Mgrado] al nuevo nodo.
    if(!nodoLleno->esHoja){
        int hijoDest = 0;
        for(int i = med + 1; i <= Mgrado; ++i){
            nuevoDer->hijos[hijoDest] = nodoLleno->hijos[i];
            nodoLleno->hijos[i] = nullptr; // higiene: lo dejamos en nullptr
            ++hijoDest;
        }
    }

    // La clave del medio es la que sube al padre.
    clavePromovida = nodoLleno->claves[med];

    // El nodo viejo se queda con las claves [0, med-1].
    nodoLleno->numClaves = med;

    // Devolvemos el nuevo nodo derecho por referencia.
    hijoNuevo = nuevoDer;
}

//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Buscar(T valor, Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return false;

    // Recorremos las claves del nodo de izquierda a derecha hasta encontrar
    // la primera que sea >= al valor buscado.
    int i = 0;
    while(i < subRaiz->numClaves && subRaiz->claves[i] < valor){
        ++i;
    }

    // Si nos detuvimos en una clave igual al valor, lo encontramos.
    if(i < subRaiz->numClaves && subRaiz->claves[i] == valor) return true;

    // Si no, bajamos al hijo correspondiente. Si es hoja, no hay donde seguir.
    if(subRaiz->esHoja) return false;

    return Buscar(valor, subRaiz->hijos[i]);
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::Podar(Nodo *subRaiz)
{
    if(subRaiz == nullptr) return;

    // Postorden: primero podamos cada hijo, luego liberamos este nodo.
    if(!subRaiz->esHoja){
        for(int i = 0; i <= subRaiz->numClaves; ++i){
            Podar(subRaiz->hijos[i]);
        }
    }

    delete subRaiz;
}

//***********************************************

template<typename T, int Mgrado>
int ArbolB<T, Mgrado>::ObtenerAltura(Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return 0;
    if(subRaiz->esHoja) return 1;
    // En un arbol B todas las hojas estan al mismo nivel, asi que basta con
    // bajar por una rama cualquiera (la del primer hijo).
    return 1 + ObtenerAltura(subRaiz->hijos[0]);
}

//***********************************
// EXCEPCIONES
//***********************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::ArbolNoMemoria::ArbolNoMemoria() throw() {}

//***********************************

template<typename T, int Mgrado>
const char *ArbolB<T, Mgrado>::ArbolNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//***********************************
// STUBS TEMPORALES (se completan en los siguientes pasos)
//***********************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Eliminar(T)
{ return false; }

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::ImprimirPorNiveles() const
{
    if(EstaVacia()) return;

    Cola<Nodo *> cola;
    Nodo *aux;

    cola.Agregar(raiz);
    cola.Agregar(nullptr); // marcador de fin de nivel

    while(!cola.EstaVacia()){

        aux = cola.ObtenerCabeza();
        cola.Eliminar();

        if(aux != nullptr){
            // Imprimimos las claves del nodo entre corchetes.
            std::cout << "[";
            for(int i = 0; i < aux->numClaves; ++i){
                std::cout << aux->claves[i];
                if(i + 1 < aux->numClaves) std::cout << ", ";
            }
            std::cout << "] ";

            // Encolamos los hijos para el siguiente nivel.
            if(!aux->esHoja){
                for(int i = 0; i <= aux->numClaves; ++i){
                    if(aux->hijos[i] != nullptr) cola.Agregar(aux->hijos[i]);
                }
            }
        }else{
            // Fin de nivel: salto de linea y, si quedan nodos, marcador nuevo.
            std::cout << std::endl;
            if(!cola.EstaVacia()){
                cola.Agregar(nullptr);
            }
        }
    }
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::ImprimirComoArbol() const
{
    if(EstaVacia()) return;
    std::cout << std::endl;
    ImprimirComoArbol(raiz, 0);
}

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Eliminar(T, Nodo*) { return false; }

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::CopiarPorNiveles(const ArbolB&) {}

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::RepararHijo(Nodo*, int) {}

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::ImprimirComoArbol(Nodo *subRaiz, int nivel) const
{
    if(subRaiz == nullptr) return;

    // Imprimimos primero el subarbol derecho con mayor sangria, luego este
    // nodo, luego el resto de subarboles. Esto da una vista "acostada" donde
    // la raiz queda al centro-izquierda y los niveles crecen hacia abajo.
    // Aqui lo hacemos sencillo: sangria por nivel + claves del nodo + hijos en orden.

    // Sangria.
    for(int i = 0; i < nivel; ++i) std::cout << "    ";

    // Claves del nodo.
    std::cout << "[";
    for(int i = 0; i < subRaiz->numClaves; ++i){
        std::cout << subRaiz->claves[i];
        if(i + 1 < subRaiz->numClaves) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Hijos recursivamente (si los hay).
    if(!subRaiz->esHoja){
        for(int i = 0; i <= subRaiz->numClaves; ++i){
            ImprimirComoArbol(subRaiz->hijos[i], nivel + 1);
        }
    }
}

//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

template<typename T, int Mgrado>
std::ostream& operator<<(std::ostream& salida, const ArbolB<T, Mgrado>& arbol)
{
    arbol.ImprimirComoArbol();
    return salida;
}
