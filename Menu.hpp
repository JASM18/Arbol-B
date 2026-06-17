/**
 * \file Menu.hpp
 * \brief Este archivo contiene las declaraciones de las funciones interactivas y utiler&iacute;a para probar el &Aacute;rbol B.
 * \author Dur&oacute;n Urbina, Angel Daniel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \author Rivera L&oacute;pez, Issac Abraham
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \date 27/05/2026
 * \code{.cpp}
 * #include <iostream>
 * #include "ArbolB.hpp"
 * #include "Menu.hpp"
 *
 * int main(){
 * try{
 * ArbolB<int> arbolPrueba(5);
 * std::cout << "--- Usando las funciones del Men\243 ---" << std::endl;
 *
 * GAgregar(arbolPrueba);
 * GAgregar(arbolPrueba);
 * std::cout << "\nImprimiendo:" << std::endl;
 * GImprimirPorNiveles(arbolPrueba);
 * std::cout << "\nN\243m. de claves:" << std::endl;
 * GNumClaves(arbolPrueba);
 * GAltura(arbolPrueba);
 * }catch(const char* mensaje){
 *     cerr << "Error: " << mensaje << endl;
 * }catch(const exception &error){
 *     cerr << "Error: " << error.what() << endl;
 * }catch(...){
 *     cerr << "El programa tuvo un error inesperado." << endl;
 * }
 *
 * return 0;
 * }
 * \endcode
 */

#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "ArbolB.hpp"

/** \brief Limpia la consola.
 * \return void
 */
void limpiarPantalla();

/** \brief Pausa el programa hasta que el usuario presione la tecla Enter.
 * \return void
 */
void pausar();

// Funciones de gestion del menu para probar la clase ArbolB.

/** \brief Funci&oacute;n para agregar un valor al &aacute;rbol B pidi&eacute;ndolo al usuario.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GAgregar(ArbolB<T> &arbol);

/** \brief Funci&oacute;n para eliminar un valor del &aacute;rbol B pidi&eacute;ndolo al usuario.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GEliminar(ArbolB<T> &arbol);

/** \brief Funci&oacute;n para buscar un valor que el usuario ingrese en el &aacute;rbol B.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GBuscar(const ArbolB<T> &arbol);

/** \brief M&eacute;todo para imprimir la cantidad total de claves almacenadas.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GNumClaves(const ArbolB<T> &arbol);

/** \brief M&eacute;todo para imprimir la altura actual del &aacute;rbol B.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GAltura(const ArbolB<T> &arbol);

/** \brief M&eacute;todo para imprimir el grado (M) de definici&oacute;n del &aacute;rbol B.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GGrado(const ArbolB<T> &arbol);

/** \brief M&eacute;todo que indica en consola si el &aacute;rbol B se encuentra vac&iacute;o.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GEstaVacia(const ArbolB<T> &arbol);

/** \brief M&eacute;todo que vac&iacute;a el &aacute;rbol B.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GVaciar(ArbolB<T> &arbol);

/** \brief M&eacute;todo que llama a la funci&oacute;n de impresi&oacute;n en orden ascendente.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GImprimirOrden(const ArbolB<T> &arbol);

/** \brief M&eacute;todo que llama a la funci&oacute;n de impresi&oacute;n por niveles.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GImprimirPorNiveles(const ArbolB<T> &arbol);

/** \brief M&eacute;todo que llama a la funci&oacute;n de impresi&oacute;n como estructura de &aacute;rbol.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbol Referencia constante al &aacute;rbol B actual.
 * \return void
 */
template<typename T>
void GImprimirComoArbol(const ArbolB<T> &arbol);

/** \brief Funci&oacute;n que inserta un n&uacute;mero espec&iacute;fico de datos aleatorios en el &aacute;rbol.
 * \tparam T Tipo de dato del &aacute;rbol.
 * \param arbolito Referencia al &aacute;rbol B donde se insertar&aacute;n los datos.
 * \return void
 */
template<typename T>
void defDatosAleatorios(ArbolB<T>& arbolito);

/** \brief Ejecuta el &aacute;rea de pruebas del &Aacute;rbol B.
 * \return void
 */
void areaPruebas();

#include "Menu.tpp"

#endif // MENU_HPP_INCLUDED
