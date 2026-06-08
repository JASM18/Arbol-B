/**
 * \file ArbolB.tpp
 * \brief Este archivo contiene la implementaci&oacute;n de los m&eacute;todos de la plantilla de clase ArbolB.
 * \author Dur&oacute;n Urbina, Angel Daniel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \author Rivera L&oacute;pez, Issac Abraham
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \date 21/05/2026
 */

#include "Cola.hpp"

//***********************************************
// CONSTRUCTOR DE NODO
//***********************************************

template<typename T>
ArbolB<T>::Nodo::Nodo(int grado) : numClaves(0), esHoja(true), claves(nullptr), hijos(nullptr)
{
    // Espacio extra para los arreglos: Mgrado claves y Mgrado+1 hijos
    // El maximo permitido es Mgrado-1 y Mgrado, pero se le pone un espacio extra para poder insertar primero y dividir despues
    try{
        claves = new T[grado];
        hijos = new Nodo*[grado + 1];

    }catch(const std::bad_alloc&){
        delete[] claves; // por si claves se asigno y hijos fallo
        throw ArbolNoMemoria();
    }

    // Se inicializa todos los punteros de los hijos a nullptr
    for(int i = 0; i <= grado; ++i){
        hijos[i] = nullptr;
    }
}

//***********************************************

template<typename T>
ArbolB<T>::Nodo::~Nodo()
{
    delete[] claves;
    delete[] hijos;
}

//***********************************************
// CONSTRUCTORES DEL ARBOL
//***********************************************

template<typename T>
ArbolB<T>::ArbolB(int M) : Mgrado(M), numClaves(0), raiz(nullptr)
{
    // numclaves = 0;
    // raiz = nullptr;
    // Mgrado = M;
    if(Mgrado < 3){
        throw ArbolGrado();
    }
}

//***********************************************

template<typename T>
ArbolB<T>::~ArbolB()
{
    Vaciar();
}

//***********************************************

template<typename T>
ArbolB<T>::ArbolB(const ArbolB &arbol) : Mgrado(arbol.Mgrado), numClaves(0), raiz(nullptr)
{
    // numClaves = 0;
    // raiz = nullptr;
    *this = arbol;
}

//***********************************************

template<typename T>
ArbolB<T> & ArbolB<T>::operator=(const ArbolB &arbol)
{
    if(this == &arbol) return *this;
    Vaciar();

    Mgrado = arbol.Mgrado; // adopta el grado del origen

    CopiarEstructura(arbol);
    return *this;
}

//***********************************************
// METODOS PUBLICOS
//***********************************************

template<typename T>
void ArbolB<T>::Agregar(T valor)
{
    // Si el arbol esta vacio, entonces se crea la raíz con ese unico valor
    if(raiz == nullptr){
        try{
            raiz = new Nodo(Mgrado);
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
            nuevaRaiz = new Nodo(Mgrado);
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

template<typename T>
bool ArbolB<T>::Eliminar(T valor)
{
    if(raiz == nullptr) return false;

    bool seElimino = Eliminar(valor, raiz);

    if(seElimino){
        --numClaves;

        // Si la raiz quedo vacia tras una fusion, la raiz baja un nivel
        // NOTA: esta es la unica forma en que el arbol decrece su altura
        if(raiz->numClaves == 0){
            Nodo *viejaRaiz = raiz;

            if(raiz->esHoja){
                // El arbol quedo completamente vacio.
                raiz = nullptr;
            }else{
                raiz = raiz->hijos[0];
                viejaRaiz->hijos[0] = nullptr;
            }
            delete viejaRaiz;
        }
    }
    return seElimino;
}

//***********************************************

template<typename T>
bool ArbolB<T>::Buscar(T valor) const
{
    return Buscar(valor, raiz);
}

//***********************************************

template<typename T>
int ArbolB<T>::ObtenerNumClaves() const
{
    return numClaves;
}

//***********************************************

template<typename T>
int ArbolB<T>::ObtenerAltura() const
{
    return ObtenerAltura(raiz);
}

//***********************************************

template<typename T>
int ArbolB<T>::ObtenerGrado() const
{
    return Mgrado;
}

//***********************************************

template<typename T>
bool ArbolB<T>::EstaVacia() const
{
    return numClaves == 0;
}

//***********************************************

template<typename T>
void ArbolB<T>::Vaciar()
{
    Podar(raiz);
    raiz = nullptr;
    numClaves = 0;
}

//***********************************************

template<typename T>
void ArbolB<T>::ImprimirOrden() const
{
    if(EstaVacia()){
        std::cout << "[ ]" << std::endl;
        return;
    }

    std::cout << "[ ";
    ImprimirOrden(raiz);
    std::cout << "\b\b]";
}

//***********************************************

template<typename T>
void ArbolB<T>::ImprimirPorNiveles() const
{
    if(EstaVacia()){
        std::cout << "[ ]" << std::endl;
        return;
    }

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

template<typename T>
void ArbolB<T>::ImprimirComoArbol() const
{
    if(EstaVacia()){
        std::cout << "[ ]" << std::endl;
        return;
    }

    std::cout << std::endl;
    ImprimirComoArbol(raiz, 0);
}


//***********************************************
// METODOS PRIVADOS
//***********************************************

template<typename T>
void ArbolB<T>::Agregar(T valor, Nodo *subRaiz, T &clavePromovida, Nodo *&hijoNuevo, bool &huboDivision)
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

template<typename T>
void ArbolB<T>::DividirNodo(Nodo *nodoLleno, T &clavePromovida, Nodo *&hijoNuevo)
{
    // El nodo ahora mismo tiene Mgrado claves: [0, 1, ..., Mgrado-1] (paso el limite permitido)

    int med = Mgrado / 2; // Indice de la clave del medio (la que sube al padre)

    // Se crea el nuevo hermano derecho
    Nodo *nuevoDer;
    try{
        nuevoDer = new Nodo(Mgrado);
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

template<typename T>
bool ArbolB<T>::Eliminar(T valor, Nodo *subRaiz)
{
    const int minClaves = (Mgrado + 1) / 2 - 1;

    int i = 0;
    while(i < subRaiz->numClaves && subRaiz->claves[i] < valor){
        ++i;
    }

    bool encontrado = (i < subRaiz->numClaves && subRaiz->claves[i] == valor);

    if(encontrado){
        if(subRaiz->esHoja){
            // Caso 1: valor en hoja, se borra directo
            for(int j = i; j < subRaiz->numClaves - 1; ++j){
                subRaiz->claves[j] = subRaiz->claves[j + 1];
            }
            --subRaiz->numClaves;
            return true;
        }else{
            // Caso 2: valor en nodo interno, se reemplaza con sucesor inorden
            Nodo *sucesorNodo = subRaiz->hijos[i + 1];
            while(!sucesorNodo->esHoja){
                sucesorNodo = sucesorNodo->hijos[0];
            }
            T sucesor = sucesorNodo->claves[0];

            subRaiz->claves[i] = sucesor;

            bool seElimino = Eliminar(sucesor, subRaiz->hijos[i + 1]);

            if(subRaiz->hijos[i + 1]->numClaves < minClaves){
                RepararHijo(subRaiz, i + 1);
            }
            return seElimino;
        }
    }else{
        // Caso 3: valor no esta aqui, bajar al hijo correspondiente
        if(subRaiz->esHoja) return false;

        bool seElimino = Eliminar(valor, subRaiz->hijos[i]);

        if(seElimino && subRaiz->hijos[i]->numClaves < minClaves){
            RepararHijo(subRaiz, i);
        }
        return seElimino;
    }
}

//***********************************************

template<typename T>
void ArbolB<T>::RepararHijo(Nodo *padre, int indiceHijo)
{
    const int minClaves = (Mgrado + 1) / 2 - 1;
    Nodo *hijo = padre->hijos[indiceHijo];

    // Intento 1: prestamo del hermano izquierdo
    // Si el hermano izquierdo tiene mas claves de las minimas, se le puede pedir prestada una
    if(indiceHijo > 0){
        Nodo *hermIzq = padre->hijos[indiceHijo - 1];
        if(hermIzq->numClaves > minClaves){

            // Se hace espacio en el hijo desplazando sus claves una posicion a la derecha
            for(int j = hijo->numClaves; j > 0; --j){
                hijo->claves[j] = hijo->claves[j - 1];
            }

            // Si no es hoja, tambien se desplazan los hijos a la derecha
            if(!hijo->esHoja){
                for(int j = hijo->numClaves + 1; j > 0; --j){
                    hijo->hijos[j] = hijo->hijos[j - 1];
                }
            }

            // La clave separadora del padre baja al inicio del hijo
            hijo->claves[0] = padre->claves[indiceHijo - 1];

            // El ultimo hijo del hermano izquierdo pasa a ser el primer hijo del hijo
            if(!hijo->esHoja){
                hijo->hijos[0] = hermIzq->hijos[hermIzq->numClaves];
            }

            // La ultima clave del hermano izquierdo sube al padre
            padre->claves[indiceHijo - 1] = hermIzq->claves[hermIzq->numClaves - 1];
            --hermIzq->numClaves;
            ++hijo->numClaves;
            return;
        }
    }

    // Intento 2: prestamo del hermano derecho
    // Si el hermano derecho tiene mas claves de las minimas, se le puede pedir prestada una
    if(indiceHijo < padre->numClaves){
        Nodo *hermDer = padre->hijos[indiceHijo + 1];
        if(hermDer->numClaves > minClaves){

            // La clave separadora del padre baja al final del hijo
            hijo->claves[hijo->numClaves] = padre->claves[indiceHijo];

            // El primer hijo del hermano derecho pasa a ser el ultimo hijo del hijo
            if(!hijo->esHoja){
                hijo->hijos[hijo->numClaves + 1] = hermDer->hijos[0];
            }
            ++hijo->numClaves;

            // La primera clave del hermano derecho sube al padre
            padre->claves[indiceHijo] = hermDer->claves[0];

            // Se desplazan las claves del hermano derecho una posicion a la izquierda
            for(int j = 0; j < hermDer->numClaves - 1; ++j){
                hermDer->claves[j] = hermDer->claves[j + 1];
            }

            // Si no es hoja, tambien se desplazan los hijos a la izquierda
            if(!hermDer->esHoja){
                for(int j = 0; j < hermDer->numClaves; ++j){
                    hermDer->hijos[j] = hermDer->hijos[j + 1];
                }
            }
            --hermDer->numClaves;
            return;
        }
    }

    // Caso 3: fusion
    // Ningun hermano puede prestar, entonces se fusionan el hijo con su hermano izquierdo
    // (o derecho si no hay izquierdo), bajando la clave separadora del padre al nodo fusionado
    int fusIzq = (indiceHijo > 0) ? indiceHijo - 1 : indiceHijo;
    Nodo *izq  = padre->hijos[fusIzq];
    Nodo *der  = padre->hijos[fusIzq + 1];

    // La clave separadora del padre baja al nodo izquierdo
    izq->claves[izq->numClaves] = padre->claves[fusIzq];
    ++izq->numClaves;

    // Se copian todas las claves del nodo derecho al izquierdo
    for(int j = 0; j < der->numClaves; ++j){
        izq->claves[izq->numClaves + j] = der->claves[j];
    }

    // Si no es hoja, se copian tambien los hijos del derecho al izquierdo
    if(!der->esHoja){
        int base = izq->numClaves;
        for(int j = 0; j <= der->numClaves; ++j){
            izq->hijos[base + j] = der->hijos[j];
            der->hijos[j] = nullptr; // higiene antes de liberar el nodo derecho
        }
    }
    izq->numClaves += der->numClaves;

    // Se elimina la clave separadora del padre y el puntero al nodo derecho
    for(int j = fusIzq; j < padre->numClaves - 1; ++j){
        padre->claves[j]    = padre->claves[j + 1];
        padre->hijos[j + 1] = padre->hijos[j + 2];
    }
    padre->hijos[padre->numClaves] = nullptr;
    --padre->numClaves;

    // Se libera el nodo derecho, sus claves e hijos ya fueron transferidos al izquierdo
    delete der;
}

//***********************************************

template<typename T>
bool ArbolB<T>::Buscar(T valor, Nodo *subRaiz) const
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

template<typename T>
int ArbolB<T>::ObtenerAltura(Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return 0;
    if(subRaiz->esHoja) return 1;

    // Como todas las hojas estan en el mismo nivel, pues se baja desde el primer hijo
    return 1 + ObtenerAltura(subRaiz->hijos[0]);
}

//***********************************************

template<typename T>
void ArbolB<T>::Podar(Nodo *subRaiz)
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

template<typename T>
void ArbolB<T>::CopiarEstructura(const ArbolB &arbolOrigen)
{
    // Para que la copia tenga *exactamente* la misma estructura que el origen
    // (misma raiz, mismos hijos, mismas claves en las mismas posiciones),
    // clonamos nodo por nodo en vez de reinsertar las claves con Agregar.
    // Si se hiciera por reinserciones, el arbol resultante podria tener la
    // misma informacion pero una forma distinta dependiendo del orden en que
    // se reinserten las claves.
    if(arbolOrigen.raiz == nullptr) return;

    raiz = ClonarNodo(arbolOrigen.raiz);
    numClaves = arbolOrigen.numClaves;
}

//***********************************************

template<typename T>
typename ArbolB<T>::Nodo *ArbolB<T>::ClonarNodo(Nodo *nodoOrigen)
{
    if(nodoOrigen == nullptr) return nullptr;

    // Creamos un nodo nuevo, copiamos sus datos basicos y sus claves.
    Nodo *copia;
    try{
        copia = new Nodo(Mgrado);
    }catch(const std::bad_alloc&){
        throw ArbolNoMemoria();
    }
    copia->numClaves = nodoOrigen->numClaves;
    copia->esHoja    = nodoOrigen->esHoja;

    for(int i = 0; i < nodoOrigen->numClaves; ++i){
        copia->claves[i] = nodoOrigen->claves[i];
    }

    // Si no es hoja, clonamos recursivamente cada uno de los hijos.
    if(!nodoOrigen->esHoja){
        for(int i = 0; i <= nodoOrigen->numClaves; ++i){
            copia->hijos[i] = ClonarNodo(nodoOrigen->hijos[i]);
        }
    }

    return copia;
}

//***********************************************

template<typename T>
void ArbolB<T>::ImprimirOrden(Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return;

    // Recorrido inorden generalizado: para cada clave, imprimimos primero el
    // subarbol que esta a su izquierda, luego la clave. Al terminar todas las
    // claves, imprimimos el ultimo subarbol derecho.
    for(int i = 0; i < subRaiz->numClaves; ++i){
        if(!subRaiz->esHoja) ImprimirOrden(subRaiz->hijos[i]);
        std::cout << subRaiz->claves[i] << ", ";
    }
    if(!subRaiz->esHoja) ImprimirOrden(subRaiz->hijos[subRaiz->numClaves]);
}

//***********************************************

template<typename T>
void ArbolB<T>::ImprimirComoArbol(Nodo *subRaiz, int nivel) const
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

//***********************************************
// EXCEPCIONES
//***********************************************

template<typename T>
ArbolB<T>::ArbolNoMemoria::ArbolNoMemoria() throw() {}

//***********************************************

template<typename T>
const char *ArbolB<T>::ArbolNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//***********************************************

template<typename T>
ArbolB<T>::ArbolGrado::ArbolGrado() throw() {}

//***********************************************

template<typename T>
const char *ArbolB<T>::ArbolGrado::what() const throw()
{
    return "Grado no valido, tiene que ser mayor o igual a 3.";
}

//***********************************************
// Flujos sobrecargados de entrada y salida
//***********************************************

template<typename T>
std::ostream& operator<<(std::ostream& salida, const ArbolB<T>& arbol)
{
    arbol.ImprimirPorNiveles();
    return salida;
}
