#ifndef ARBOLB_HPP
#define ARBOLB_HPP

#include <iostream>
#include <exception>

// Un arbol B se define dado un grado M
// Cada nodo tiene ahora una lista de valores, no como en el arbolAVL que este tiene solo un valor
// La cardinalidad de esta lista se le denomina "claves", si el el grado es M=5, cada nodo tiene a lo mucho 4 claves

// Cada nodo (excepto la raiz y hojas) puede tener entre M/2 y M hijos
// Cada nodo (excepto la raiz) puede tener entre M/2-1 y M-1 claves
// La raiz puede tener entre 2 y M hijos
// Si un nodo tiene exactamente k claves, entonces esta tiene k+1 hijos

// Ejemplo: Un arbol B con grado M=5:
// - Cada nodo tiene entre 3 y 5 hijos, y entre 2 y 4 claves
// - la raiz puede tener entre 1 y 4 claves

// La lista de un nodo esta ordenada: (k_1 < k_2 < ... < k_{M-1})
// Entre cada una de esas claves, hay un hijo -> |k_1|k_2|...|k_{M-1}| en donde el simbolo '|' denota que ahi hay un puntero a hijo
// Aqui el chiste es que todos los valores que se almacenan en los hijos sigue estando ordenado:
// es decir, todas las claves del hijo que esta por ejemplo en |k_1 son menores que la clave k_1
// todas las claves que estan entre k_1|k_2 estan en el rango de k_1 < hijo < k_2 y asi sucesivamente...

// Todas las hojas estan al mismo nivel

// === Estructura de un nodo ===
// T *claves -> [0, 1, ..., Mgrado-1]: arreglo dinamico con a lo mucho Mgrado-1 claves (uno mas para detectar overflow)
// Nodo **hijos -> [0, 1, ..., Mgrado]: arreglo dinamico de punteros a hijos (uno mas para detectar overflow)
// numClaves: cantidad de claves actuales en el nodo
// esHoja: indicador para saber si es hoja

// La operacion de dividir el arbol se ejecuta cuando se intenta tener mas claves de las permitidas
// (Mgrado claves cuando a lo mucho se puede Mgrado-1). La clave del medio (indice Mgrado/2) sube al padre.

//***********************************************

template<typename T, int Mgrado> class ArbolB;
template<typename T, int Mgrado>
std::ostream& operator<<(std::ostream& salida, const ArbolB<T, Mgrado>& arbol);

//***********************************************

template <typename T, int Mgrado>
class ArbolB {
    friend std::ostream& operator<< <>(std::ostream& salida, const ArbolB<T, Mgrado>& arbol);
public:

    // Constructores
    ArbolB();
    ~ArbolB();
    ArbolB(const ArbolB& arbol);
    ArbolB& operator=(const ArbolB& arbol);

    // Metodos publicos
    void Agregar(T valor);
    bool Eliminar(T valor);
    bool Buscar(T valor) const;

    int ObtenerNumClaves() const;
    int ObtenerAltura() const;
    int ObtenerGrado() const;

    bool EstaVacia() const;
    void Vaciar();

    void ImprimirOrden() const; // Falta
    void ImprimirPorNiveles() const;
    void ImprimirComoArbol() const;

    /**
     * \brief Excepcion lanzada cuando ocurren fallos de memoria dinamica.
     */
    class ArbolNoMemoria : public std::exception {
    public:
        ArbolNoMemoria() throw();
        virtual const char *what() const throw();
    };

private:

    int numClaves; // Total de claves en todo el arbol

    struct Nodo {
        int numClaves;  // Cuantas claves hay actualmente en este nodo
        bool esHoja;    // Indica si este nodo no tiene hijos
        T *claves;      // Arreglo dinamico de tamano Mgrado (uno mas que el maximo)
        Nodo **hijos;   // Arreglo dinamico de tamano Mgrado+1 (uno mas que el maximo)

        Nodo();   // Pide memoria para claves y hijos
        ~Nodo();  // Libera la memoria de los arreglos (no destruye recursivamente)
    }*raiz;

    // =====================
    // Funciones de utileria
    // =====================

    // Agregar usa el estilo "hacia arriba": la funcion privada recursiva inserta en la hoja correspondiente;
    // si hubo division, regresa por referencia la clave promovida y el nuevo nodo derecho
    // El llamador (el padre) decide si tambien se desborda o no
    void Agregar(T valor, Nodo *subRaiz, T &clavePromovida, Nodo *&hijoNuevo, bool &huboDivision);
    void DividirNodo(Nodo *nodoLleno, T &clavePromovida, Nodo *&hijoNuevo); // Cuando el nodo este overflow (tiene mas de M hijos)

    // Eliminar tambien va hacia arriba: tras borrar en una hoja o reemplazar en un nodo interno,
    // si el hijo quedo con underflow (menos de M/2 hijos), entonces el padre lo repara (prestamo o fusion) al regresar la recursion
    bool Eliminar(T valor, Nodo *subRaiz);
    void RepararHijo(Nodo *padre, int indiceHijo);   // prestamo o fusion para cuando el nodo este en underflow (menos de M/2 hijos)

    // ===== mas cositas =====
    int ObtenerAltura(Nodo *subRaiz) const; // Auxiliar para buscar la altura del arbol recursivamente

    bool Buscar(T valor, Nodo *subRaiz) const;
    void Podar(Nodo *subRaiz); // Auxiliar para vaciar recursivamente

    void CopiarEstructura(const ArbolB &arbolOrigen);
    Nodo *ClonarNodo(Nodo *nodoOrigen);

    void ImprimirComoArbol(Nodo *subRaiz, int nivel) const;
};

#include "ArbolB.tpp"

#endif // ARBOLB_HPP
