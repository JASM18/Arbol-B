/**
 * \file ArbolB.hpp
 * Este archivo contiene la definici&oacute;n de la plantilla de clase ArbolB.
 * \author Dur&oacute;n Urbina, Angel Daniel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \author Rivera L&oacute;pez, Issac Abraham
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \date 21/05/2026
 * \code{.cpp}
//falta el codigo
 * \endcode
 */

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

// Declaraciones adelantadas necesarias para que el operador << sea amigo de la clase
template<typename T> class ArbolB;
template<typename T>
std::ostream& operator<<(std::ostream& salida, const ArbolB<T>& arbol);

//***********************************************

/**
 * \brief Plantilla de clase que implementa la estructura de datos &Aacute;rbol B.
 *
 * \tparam T Tipo de dato que almacenar&aacute; el &aacute;rbol.
 */
template <typename T>
class ArbolB {

    /** \brief Sobrecarga del operador de inserci&oacute;n para imprimir el &aacute;rbol por niveles.
     * \param salida Flujo de salida.
     * \param arbol Referencia constante al &aacute;rbol a imprimir.
     * \return Referencia al flujo de salida modificado.
     */
    friend std::ostream& operator<< <>(std::ostream& salida, const ArbolB<T>& arbol);

public:

    // Constructores

    /** \brief Constructor que inicializa el &aacute;rbol B definiendo su grado m&aacute;ximo.
     * \param M N&uacute;mero entero que define el grado del &aacute;rbol (m&iacute;nimo 3).
     * \throw ArbolGrado Lanza excepci&oacute;n si el grado M es menor a 3.
     */
    ArbolB(int M);

    /** \brief Destructor por default que libera toda la memoria din&aacute;mica del &aacute;rbol.
     */
    ~ArbolB();

    /** \brief Constructor de copias que inicializa un &aacute;rbol a partir de otro existente.
     * \param arbol Referencia constante al &aacute;rbol que se desea copiar.
     */
    ArbolB(const ArbolB& arbol);

    /** \brief Operador de asignaci&oacute;n sobrecargado.
     * \param arbol Referencia constante al &aacute;rbol origen.
     * \return Una referencia al &aacute;rbol actual (*this).
     */
    ArbolB& operator=(const ArbolB& arbol);

    // Metodos publicos

    /** \brief M&eacute;todo para agregar un nuevo elemento al &aacute;rbol.
     * \param valor Dato a insertar.
     * \return void
     * \throw ArbolNoMemoria Lanza excepci&oacute;n si falla la asignaci&oacute;n de memoria.
     */
    void Agregar(T valor);

    /** \brief M&eacute;todo para eliminar un elemento del &aacute;rbol.
     * \param valor Dato a eliminar.
     * \return true si se elimin&oacute; correctamente, false si no se encontr&oacute;.
     */
    bool Eliminar(T valor);

    /** \brief M&eacute;todo para buscar un elemento en el &aacute;rbol.
     * \param valor Dato a buscar.
     * \return true si el valor se encuentra, false en caso contrario.
     */
    bool Buscar(T valor) const;

    /** \brief M&eacute;todo para obtener la cantidad total de claves en el &aacute;rbol.
     * \return N&uacute;mero entero con el total de claves.
     */
    int ObtenerNumClaves() const;

    /** \brief M&eacute;todo para obtener la altura actual del &aacute;rbol.
     * \return N&uacute;mero entero que representa la altura.
     */
    int ObtenerAltura() const;

    /** \brief M&eacute;todo para obtener el grado del &aacute;rbol B.
     * \return N&uacute;mero entero que representa el grado M.
     */
    int ObtenerGrado() const;

    /** \brief M&eacute;todo para consultar si el &aacute;rbol est&aacute; vac&iacute;o.
     * \return true si no tiene elementos, false en caso contrario.
     */
    bool EstaVacia() const;

    /** \brief M&eacute;todo para vaciar el &aacute;rbol y liberar su memoria.
     * \return void
     */
    void Vaciar();

    /** \brief M&eacute;todo para imprimir los elementos del &aacute;rbol en orden.
     * \return void
     */
    void ImprimirOrden() const; // Falta

    /** \brief M&eacute;todo para imprimir los elementos del &aacute;rbol agrupados por niveles.
     * \return void
     */
    void ImprimirPorNiveles() const;

    /** \brief M&eacute;todo para imprimir los elementos del &aacute;rbol mostrando su estructura visual.
     * \return void
     */
    void ImprimirComoArbol() const;

    /**
     * \brief Excepci&oacute;n lanzada cuando ocurren fallos de memoria din&aacute;mica.
     */
    class ArbolNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ArbolNoMemoria.
         */
        ArbolNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no hay memoria disponible.
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

    /**
     * \brief Excepci&oacute;n lanzada cuando se define un grado no v&aacute;lido.
     */
    class ArbolGrado : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ArbolGrado.
         */
        ArbolGrado() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando el grado es inv&aacute;lido.
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:
    int Mgrado;         ///< Grado m&aacute;ximo del &aacute;rbol B.
    int numClaves;      ///< Total de claves en todo el &aacute;rbol.

    /**
     * \brief Estructura interna que representa un nodo en el &aacute;rbol B.
     */
    struct Nodo {
        int numClaves;  ///< Cuantas claves hay actualmente en este nodo.
        bool esHoja;    ///< Indica si este nodo no tiene hijos.
        T *claves;      ///< Arreglo din&aacute;mico de tama&ntilde;o Mgrado (uno mas que el m&aacute;ximo).
        Nodo **hijos;   ///< Arreglo din&aacute;mico de tama&ntilde;o Mgrado+1 (uno mas que el m&aacute;ximo).

        /** \brief Constructor de la estructura Nodo.
         * \param grado Grado del &aacute;rbol para reservar los arreglos din&aacute;micos.
         */
        Nodo(int grado);   // Pide memoria para claves y hijos

        /** \brief Destructor de la estructura Nodo.
         */
        ~Nodo();  // Libera la memoria de los arreglos (no destruye recursivamente)
    }*raiz;             ///< Puntero al nodo ra&iacute;z del &aacute;rbol B.

    // =====================
    // Funciones de utileria
    // =====================

    // Agregar usa el estilo "hacia arriba": la funcion privada recursiva inserta en la hoja correspondiente;
    // si hubo division, regresa por referencia la clave promovida y el nuevo nodo derecho
    // El llamador (el padre) decide si tambien se desborda o no

    /** \brief M&eacute;todo auxiliar para agregar un elemento recursivamente.
     * \param valor Dato a insertar.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \param clavePromovida Referencia para devolver la clave que sube al padre en caso de divisi&oacute;n.
     * \param hijoNuevo Referencia para devolver el nuevo nodo derecho en caso de divisi&oacute;n.
     * \param huboDivision Referencia booleana que indica si el nodo actual se dividi&oacute;.
     * \return void
     */
    void Agregar(T valor, Nodo *subRaiz, T &clavePromovida, Nodo *&hijoNuevo, bool &huboDivision);

    /** \brief M&eacute;todo auxiliar para dividir un nodo que ha excedido su capacidad de claves.
     * \param nodoLleno Puntero al nodo que ha excedido su capacidad.
     * \param clavePromovida Referencia para devolver la clave que subir&aacute; al padre.
     * \param hijoNuevo Referencia para devolver el nuevo nodo creado por la divisi&oacute;n.
     * \return void
     */
    void DividirNodo(Nodo *nodoLleno, T &clavePromovida, Nodo *&hijoNuevo); // Cuando el nodo este overflow (tiene mas de M hijos)

    // Eliminar tambien va hacia arriba: tras borrar en una hoja o reemplazar en un nodo interno,
    // si el hijo quedo con underflow (menos de M/2 hijos), entonces el padre lo repara (prestamo o fusion) al regresar la recursion

    /** \brief M&eacute;todo auxiliar para eliminar un elemento recursivamente.
     * \param valor Dato a eliminar.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \return true si el valor fue eliminado en el sub&aacute;rbol, false en caso contrario.
     */
    bool Eliminar(T valor, Nodo *subRaiz);

    /** \brief M&eacute;todo auxiliar para reparar un nodo hijo que ha quedado con menos claves de las permitidas.
     * \param padre Puntero al nodo padre.
     * \param indiceHijo &Iacute;ndice del hijo que necesita reparaci&oacute;n (pr&eacute;stamo o fusi&oacute;n).
     * \return void
     */
    void RepararHijo(Nodo *padre, int indiceHijo);   // prestamo o fusion para cuando el nodo este en underflow (menos de M/2 hijos)

    // ===== mas cositas =====

    /** \brief M&eacute;todo auxiliar para obtener la altura del &aacute;rbol recursivamente.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \return N&uacute;mero entero que representa la altura del sub&aacute;rbol.
     */
    int ObtenerAltura(Nodo *subRaiz) const; // Auxiliar para buscar la altura del arbol recursivamente

    /** \brief M&eacute;todo auxiliar para buscar un elemento recursivamente.
     * \param valor Dato a buscar.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \return true si el valor fue encontrado, false en caso contrario.
     */
    bool Buscar(T valor, Nodo *subRaiz) const;

    /** \brief M&eacute;todo auxiliar para vaciar recursivamente el &aacute;rbol.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \return void
     */
    void Podar(Nodo *subRaiz); // Auxiliar para vaciar recursivamente

    /** \brief M&eacute;todo auxiliar para copiar recursivamente la estructura completa de un &aacute;rbol.
     * \param arbolOrigen Referencia constante al &aacute;rbol origen que se va a copiar.
     * \return void
     */
    void CopiarEstructura(const ArbolB &arbolOrigen);

    /** \brief M&eacute;todo auxiliar para clonar un nodo espec&iacute;fico.
     * \param nodoOrigen Puntero al nodo que se desea clonar.
     * \return Puntero al nuevo nodo clonado.
     */
    Nodo *ClonarNodo(Nodo *nodoOrigen);

    /** \brief M&eacute;todo auxiliar para imprimir los elementos del &aacute;rbol en orden recursivamente.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \return void
     */
    void ImprimirOrden(Nodo *subRaiz) const;

    /** \brief M&eacute;todo auxiliar para imprimir los elementos del &aacute;rbol mostrando su estructura visual recursivamente.
     * \param subRaiz Nodo actual en la recursi&oacute;n.
     * \param nivel Nivel actual de profundidad para ajustar la indentaci&oacute;n.
     * \return void
     */
    void ImprimirComoArbol(Nodo *subRaiz, int nivel) const;
};

#include "ArbolB.tpp"

#endif // ARBOLB_HPP
