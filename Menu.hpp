#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "ArbolB.hpp"

/**
 * @brief Llena el arbol con `numDatos` enteros aleatorios.
 *
 *  El rango se calcula automaticamente como [1, numDatos * 10].
 *  Si Agregar() retorna false (duplicado), el valor se omite y se reporta.
 *
 * @param arbolito Referencia al arbol que se va a llenar.
 * @param numDatos Cantidad de inserciones a intentar.
 */
template<typename T, int Mgrado>
void defDatosAleatorios(ArbolB<T, Mgrado>& arbolito, int numDatos);

#include "Menu.tpp"

#endif // MENU_HPP_INCLUDED
