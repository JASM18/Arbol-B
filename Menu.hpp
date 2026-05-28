#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "ArbolB.hpp"

void limpiarPantalla();

void pausar();

// Funciones de gestion del menu para probar la clase ArbolB.

template<typename T>
void GAgregar(ArbolB<T> &arbol);

template<typename T>
void GEliminar(ArbolB<T> &arbol);

template<typename T>
void GBuscar(const ArbolB<T> &arbol);

template<typename T>
void GNumClaves(const ArbolB<T> &arbol);

template<typename T>
void GAltura(const ArbolB<T> &arbol);

template<typename T>
void GGrado(const ArbolB<T> &arbol);

template<typename T>
void GEstaVacia(const ArbolB<T> &arbol);

template<typename T>
void GVaciar(ArbolB<T> &arbol);

template<typename T>
void GImprimirOrden(const ArbolB<T> &arbol);

template<typename T>
void GImprimirPorNiveles(const ArbolB<T> &arbol);

template<typename T>
void GImprimirComoArbol(const ArbolB<T> &arbol);

template<typename T>
void defDatosAleatorios(ArbolB<T>& arbolito);

#include "Menu.tpp"

#endif // MENU_HPP_INCLUDED
