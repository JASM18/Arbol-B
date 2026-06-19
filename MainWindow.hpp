#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsScene>
#include "VistaZoom.hpp"
#include "ArbolB.hpp"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBotonInsertarClic();
    void onBotonEliminarClic();
    void onBotonBuscarClic();
    void onBotonVaciarClic();
    void onBotonAleatorioClic();
    void onBotonCambiarGradoClic();

private:
    QLineEdit *cajaTexto;
    QLineEdit *cajaCantidadAleatorios;
    QPushButton *botonInsertar;
    QPushButton *botonEliminar;
    QPushButton *botonBuscar;
    QPushButton *botonVaciar;
    QPushButton *botonAleatorio;
    QPushButton *botonCambiarGrado;
    QPushButton *botonCerrar;
    QLabel *etiquetaInfo;

    QGraphicsScene *escena;
    VistaZoom *vistaGrafica;
    ArbolB<int> *arbol;

    bool hayBusqueda = false;
    int claveBuscada = 0;

    void configurarInterfaz();
    void actualizarLienzo();

    // --- Dibujo del árbol con layout de dos pasadas ---
    // Pasada 1: calcula cuánto ancho necesita cada subárbol.
    int calcularAnchoSubarbol(const ArbolB<int>::NodoVista &nodo);
    // Ancho en píxeles de la caja de un nodo según sus claves.
    int anchoDeCaja(const ArbolB<int>::NodoVista &nodo);
    // Pasada 2: dibuja cada nodo centrado en centroX, repartiendo a los hijos
    // el ancho que cada uno necesita.
    void dibujarNodoRecursivo(const ArbolB<int>::NodoVista &nodo, int centroX, int y);
};

#endif // MAINWINDOW_HPP
