#include "Cola.hpp"

//***********************************************
// CONSTRUCTORES DEL ARBOL
//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::ArbolB() : numClaves(0), raiz(nullptr)
{
    // numclaves = 0;
    // raiz = nullptr;
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
    // numClaves = 0;
    // raiz = nullptr;
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
// CONSTRUCTOR DE NODO
//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::Nodo::Nodo() : numClaves(0), esHoja(true), claves(nullptr), hijos(nullptr)
{
    // Espacio extra para los arreglos: Mgrado claves y Mgrado+1 hijos
    // El maximo permitido es Mgrado-1 y Mgrado, pero se le pone un espacio extra para poder insertar primero y dividir despues
    try{
        claves = new T[Mgrado];
        hijos = new Nodo*[Mgrado + 1];

    }catch(const std::bad_alloc&){
        delete[] claves; // por si claves se asigno y hijos fallo
        throw ArbolNoMemoria();
    }

    // Se inicializa todos los punteros de los hijos a nullptr
    for(int i = 0; i <= Mgrado; ++i){
        hijos[i] = nullptr;
    }
}

//***********************************************

template<typename T, int Mgrado>
ArbolB<T, Mgrado>::Nodo::~Nodo()
{
    delete[] claves;
    delete[] hijos;
}

//***********************************************
// METODOS PUBLICOS
//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::Agregar(T valor)
{
    // Si el arbol esta vacio, entonces se crea la raíz con ese unico valor
    if(raiz == nullptr){
        try{
            raiz = new Nodo();
        }catch(const std::bad_alloc&){
            throw ArbolNoMemoria();
        }
        raiz->claves[0] = valor;
        raiz->numClaves = 1;
        ++numClaves;
        return;
    }

    // Como el arbol no esta vacio, entonces se inserta recursivamente
    T clavePromovida; // Elemento de en medio que se le dará al padre en caso de si hubo division
    Nodo *hijoNuevo = nullptr; // Hijo derecho resultande por la división (si es que la hay)
    bool huboDivision = false;

    Agregar(valor, raiz, clavePromovida, hijoNuevo, huboDivision);

    // Si la raiz se dividio durante la recursion, entonces se necesita crear una nueva raiz
    // NOTA: Esta es la unica forma en que un arbol B crece en altura
    if(huboDivision){

        Nodo *nuevaRaiz;

        try{
            nuevaRaiz = new Nodo();
        }catch(const std::bad_alloc&){
            throw ArbolNoMemoria();
        }

        // Conexión manual
        nuevaRaiz->esHoja = false;
        nuevaRaiz->numClaves = 1;
        nuevaRaiz->claves[0] = clavePromovida;
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->hijos[1] = hijoNuevo;
        raiz = nuevaRaiz;
    }

    ++numClaves;
}
//***********************************************

// Aquí va Eliminar() (el prototipo de Eliminar() esta abajo del codigo)

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
void ArbolB<T, Mgrado>::Agregar(T valor, Nodo *subRaiz, T &clavePromovida, Nodo *&hijoNuevo, bool &huboDivision)
{
    // Primero hay que encontrar la posicion donde iria el valor
    // Se usa '<=' para que las claves iguales se acumulen a la derecha (la profe dijo que los duplicados se permiten)
    int i = 0;

    while(i < subRaiz->numClaves && subRaiz->claves[i] <= valor){
        ++i;
    }

    //  Si estamos en una hoja, se intenta insertar ahí mero, de lo contrario se baja al hijo de forma recursiva hasta que sea hoja
    if(subRaiz->esHoja){

        // Se inserta la clave en posicion i, corriendo las demas a la derecha.
        for(int j = subRaiz->numClaves ; j > i ; --j){
            subRaiz->claves[j] = subRaiz->claves[j - 1]; // se mueven los elementos +1 pocisión
        }

        subRaiz->claves[i] = valor;
        ++subRaiz->numClaves;

    }else{

        // Aquí se controla la división, se baja al hijo 'i' cuando se llama a Agregar(...->hijos[i]), si hubo división, entonces aquí es donde el padre debe de tomar la clave promovida por el hijo

        T clavePromHijo;
        Nodo *hijoNuevoSub = nullptr;
        bool huboDivisionSub = false;

        Agregar(valor, subRaiz->hijos[i], clavePromHijo, hijoNuevoSub, huboDivisionSub);

        if(huboDivisionSub){
            // Se agrega clavePromHijo en posicion 'i' y hijoNuevoSub en posicion i+1
            for(int j = subRaiz->numClaves; j > i; --j){
                subRaiz->claves[j] = subRaiz->claves[j - 1];
                subRaiz->hijos[j + 1] = subRaiz->hijos[j];
            }

            subRaiz->claves[i] = clavePromHijo;
            subRaiz->hijos[i + 1] = hijoNuevoSub;
            ++subRaiz->numClaves;
        }
    }

    // Si tras agregar esa nueva clave/nodo se excedio, entonces se debe de dividir y se le reporta al padre (cuando termina la función)
    if(subRaiz->numClaves == Mgrado){
        DividirNodo(subRaiz, clavePromovida, hijoNuevo);
        huboDivision = true;
    }else{
        huboDivision = false;
    }
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::DividirNodo(Nodo *nodoLleno, T &clavePromovida, Nodo *&hijoNuevo)
{
    // El nodo ahora mismo tiene Mgrado claves: [0, 1, ..., Mgrado-1] (paso el limite permitido)

    int med = Mgrado / 2; // Indice de la clave del medio (la que sube al padre)

    // Se crea el nuevo hermano derecho
    Nodo *nuevoDer;
    try{
        nuevoDer = new Nodo();
    }catch(const std::bad_alloc&){
        throw ArbolNoMemoria();
    }

    nuevoDer->esHoja = nodoLleno->esHoja;

    // Se copian las claves [med+1, Mgrado-1] al nuevo nodo
    int claveDest = 0;

    for(int i = med + 1; i < Mgrado; ++i){
        nuevoDer->claves[claveDest] = nodoLleno->claves[i];
        ++claveDest;
    }
    nuevoDer->numClaves = claveDest;

    // Si no es hoja, se copia tambien los hijos [med+1, Mgrado] al nuevo nodo
    if(!nodoLleno->esHoja){

        int hijoDest = 0;

        for(int i = med + 1; i <= Mgrado; ++i){
            nuevoDer->hijos[hijoDest] = nodoLleno->hijos[i];
            nodoLleno->hijos[i] = nullptr; // Los punteros del nodo izquiero (el que antes estaba lleno) ahora serán nulos
            ++hijoDest;
        }
    }

    clavePromovida = nodoLleno->claves[med]; // La clave del medio es la que sube al padre.

    nodoLleno->numClaves = med; // El nodo de la izquierda se queda con las claves [0, med-1].

    // Devolvemos el nuevo nodo derecho por referencia.
    hijoNuevo = nuevoDer;
}


//***********************************************

template<typename T, int Mgrado>
bool ArbolB<T, Mgrado>::Buscar(T valor, Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return false;

    // Se recorre el arreglo de claves hasta encontrar la primera que sea >= al valor buscado.
    int i = 0;
    while(i < subRaiz->numClaves && subRaiz->claves[i] < valor){
        ++i;
    }

    // Si se detuvo una clave igual al valor, se encontro wiiiii :D
    if(i < subRaiz->numClaves && subRaiz->claves[i] == valor) return true;

    // Si no, se baja al hijo correspondiente PERO Si es hoja, entonces no hay donde seguir pipipi
    if(subRaiz->esHoja) return false;

    return Buscar(valor, subRaiz->hijos[i]);
}

//***********************************************

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::Podar(Nodo *subRaiz)
{
    if(subRaiz == nullptr) return;

    // Postorden: primero se poda cada hijo, luego se libera ese nodo.
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

    // Como todas las hojas estan en el mismo nivel, pues se baja desde el primer hijo
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
{
    return false;
}

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
bool ArbolB<T, Mgrado>::Eliminar(T, Nodo*)
{
    return false;
}

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::CopiarPorNiveles(const ArbolB&)
{

}

template<typename T, int Mgrado>
void ArbolB<T, Mgrado>::RepararHijo(Nodo*, int)
{

}

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
