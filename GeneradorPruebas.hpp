#ifndef GENERADOR_PRUEBAS_HPP
#define GENERADOR_PRUEBAS_HPP

/**
 * @brief Módulo para llenar un Arbol B con números aleatorios.
 * * @tparam T Tipo de dato del árbol.
 * @tparam Mgrado Grado del árbol.
 * @param arbol Referencia al árbol B que se va a llenar.
 * @param cantidad Cantidad de números a generar.
 * @param min_val Valor mínimo del rango aleatorio.
 * @param max_val Valor máximo del rango aleatorio.
 */
template<typename T, int Mgrado>
void LlenarArbolAleatorio(ArbolB<T, Mgrado>& arbol, int cantidad, T min_val, T max_val);

#include "GeneradorPruebas.tpp" // Incluimos la implementación de la función plantilla

#endif // GENERADOR_PRUEBAS_HPP