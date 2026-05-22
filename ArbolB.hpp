#ifndef ARBOLB_HPP
#define ARBOLB_HPP

#include <iostream>
#include <exception>

// Un arbol B se define dado un grado M
// Cada nodo tiene ahora una lista de valores, no como en el arbolAVL que este tiene solo un valor
// La cardinalidad de esta lista se le denomina "claves", si el el grado es M=5, cada nodo tiene a lo mucho 4 claves

// Cada nodo (excepto la raiz) puede tener entre M/2 y M hijos
// Cada nodo (excepto la raiz) puede tener entre M/2-1 y M-1 claves
// La raíz puede tener entre 2 y M hijos
// Si un nodo tiene exactamente k claves, entonces esta tiene k+1 hijos

// Ejemplo: Un arbol B con grado M=5:
// - Cada nodo tiene entre 3 y 5 hijos, y entre 2 y 4 claves
// - la raíz puede tener ntre 1 y 4 claves

// La lista de un nodo esta ordenada: (k_1 < k_2 < ... < k_{M-1})
// Entre cada una de esas claves, hay un hijo -> |k_1|k_2|...|k_{M-1}| en donde el simbolo '|' denota que ahí hay un puntero a hijo
// Aquí el chiste es que todos los valores que se almacenan en los hijos sigue estando ordenado:
// es decir, todas las claves del hijo que esta por ejemplo en |k_1 son menores que la clave k_1
// todas las claves que estan entre k_1|k_2 estan en el rango de k_1 < hijo < k_2 y aspi sucesivamente...

// Todas las hijas estan al mismo nivel

// === Estructura de un nodo ===
// T *claves esta apuntando -> [0, 1, ..., M-1]: arreglo dinamico con a lo mucho M-1 claves
// Nodo **hijos esta apuntando -> [0, 1, ..., M]: arreglo dinamico de punteros a hijos nodo
// numClaves: cantidad de claves actuales en el nodo
// esHoja: indicador pa ver si es hoja
template <typename T>
class ArbolB {
public:

    // Constructores
    ArbolB();
    ~ArbolB();
    ArbolB(const ArbolB& other);
    ArbolB& operator=(const ArbolB& other);

    // Métodos publicos
    void Agregar(T valor);
    bool Buscar(T valor) const;
    void Imprimir() const;

    int ObtenerNumNodos() const;
    int ObtenerAltura() const;

    bool EstaVacia() const;
    void Vaciar();

    /**
     * \brief Excepci&oacute;n lanzada cuando ocurren fallos de memoria din&aacute;mica.
     */
    class ArbolNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ArbolNoMemoria.
         */
        ArbolNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:

    int Mgrado; // Grado del ArbolB M (tiene que ser mayor o igual a 3: Mgrado >= 3)


    struct Nodo {
        int numClaves; // Cuantas claves hay en la lista de claves || cardinalidad de la lista
        bool esHoja; // Para saber si sus punteros de hijos son nulos
        T *claves; // Arreglo dinamico que contiene las claves (a lo mucho tiene Mgrado-1 claves)
        Nodo **hijos; // Arreglo dinamico que contiene los punteros de sus hijos

        Nodo(int grado); // Constructor del nodo, recibe 'grado' para construir el arreglo dinamico
        ~Nodo(); // Destructor del nodo
    };


};

#include "ArbolB.tpp"

#endif // ARBOL B_HPP
