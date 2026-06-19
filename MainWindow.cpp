#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QString>
#include <QInputDialog>
#include <QIntValidator>
#include <QRandomGenerator>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    int gradoM = QInputDialog::getInt(this, "Configuración del Árbol B", "Ingrese el grado M:", 5, 3, 20);
    arbol = new ArbolB<int>(gradoM);
    configurarInterfaz();
    actualizarLienzo();
}

MainWindow::~MainWindow() {
    delete arbol;
}

void MainWindow::configurarInterfaz() {
    this->setWindowTitle("Árbol B - Gestor Gráfico");
    this->resize(1000, 700);

    QLabel *etiquetaValor = new QLabel("Valor:");
    cajaTexto = new QLineEdit();
    botonInsertar = new QPushButton("Insertar");
    botonEliminar = new QPushButton("Eliminar");
    botonBuscar = new QPushButton("Buscar");
    botonVaciar = new QPushButton("Vaciar");
    botonCambiarGrado = new QPushButton("Cambiar grado");

    botonAleatorio = new QPushButton("Datos aleatorios");
    QLabel *etiquetaCantidad = new QLabel("Cantidad:");
    cajaCantidadAleatorios = new QLineEdit("15");
    cajaCantidadAleatorios->setFixedWidth(50);
    cajaCantidadAleatorios->setValidator(new QIntValidator(1, 9999, this));

    // Botón para cerrar todo el programa
    botonCerrar = new QPushButton("Cerrar");
    botonCerrar->setStyleSheet("QPushButton { background-color: #b33; color: white; font-weight: bold; }");

    connect(botonInsertar, &QPushButton::clicked, this, &MainWindow::onBotonInsertarClic);
    connect(botonEliminar, &QPushButton::clicked, this, &MainWindow::onBotonEliminarClic);
    connect(botonBuscar, &QPushButton::clicked, this, &MainWindow::onBotonBuscarClic);
    connect(botonVaciar, &QPushButton::clicked, this, &MainWindow::onBotonVaciarClic);
    connect(botonAleatorio, &QPushButton::clicked, this, &MainWindow::onBotonAleatorioClic);
    connect(botonCambiarGrado, &QPushButton::clicked, this, &MainWindow::onBotonCambiarGradoClic);
    connect(cajaTexto, &QLineEdit::returnPressed, this, &MainWindow::onBotonInsertarClic);
    // El botón Cerrar llama directamente a qApp->quit() para terminar la aplicación
    connect(botonCerrar, &QPushButton::clicked, qApp, &QApplication::quit);

    QHBoxLayout *layoutControles = new QHBoxLayout();
    layoutControles->addWidget(etiquetaValor);
    layoutControles->addWidget(cajaTexto);
    layoutControles->addWidget(botonInsertar);
    layoutControles->addWidget(botonEliminar);
    layoutControles->addWidget(botonBuscar);
    layoutControles->addWidget(botonVaciar);
    layoutControles->addWidget(botonCambiarGrado);
    layoutControles->addSpacing(20);
    layoutControles->addWidget(botonAleatorio);
    layoutControles->addWidget(etiquetaCantidad);
    layoutControles->addWidget(cajaCantidadAleatorios);
    layoutControles->addStretch();
    layoutControles->addWidget(botonCerrar);   // a la derecha del todo

    etiquetaInfo = new QLabel();
    etiquetaInfo->setStyleSheet("QLabel { color: white; font-weight: bold; padding: 4px; }");

    escena = new QGraphicsScene(this);
    vistaGrafica = new VistaZoom(escena);
    vistaGrafica->setBackgroundBrush(Qt::darkGray);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addLayout(layoutControles);
    layoutPrincipal->addWidget(etiquetaInfo);
    layoutPrincipal->addWidget(vistaGrafica);
}

void MainWindow::onBotonInsertarClic() {
    QString texto = cajaTexto->text();
    if(texto.isEmpty()) return;
    bool ok;
    int valor = texto.toInt(&ok);
    if(!ok){ cajaTexto->clear(); return; }
    arbol->Agregar(valor);
    hayBusqueda = false;
    cajaTexto->clear();
    actualizarLienzo();
}

void MainWindow::onBotonEliminarClic() {
    QString texto = cajaTexto->text();
    if(texto.isEmpty()) return;
    bool ok;
    int valor = texto.toInt(&ok);
    if(!ok){ cajaTexto->clear(); return; }
    arbol->Eliminar(valor);
    hayBusqueda = false;
    cajaTexto->clear();
    actualizarLienzo();
}

void MainWindow::onBotonBuscarClic() {
    QString texto = cajaTexto->text();
    if(texto.isEmpty()) return;
    bool ok;
    int valor = texto.toInt(&ok);
    if(!ok){ cajaTexto->clear(); return; }
    hayBusqueda = true;
    claveBuscada = valor;
    cajaTexto->clear();
    actualizarLienzo();
}

void MainWindow::onBotonVaciarClic() {
    arbol->Vaciar();
    hayBusqueda = false;
    actualizarLienzo();
}

void MainWindow::onBotonAleatorioClic() {
    bool ok;
    int cantidad = cajaCantidadAleatorios->text().toInt(&ok);
    if(!ok || cantidad < 1) cantidad = 15;
    for(int i = 0; i < cantidad; ++i){
        int valor = QRandomGenerator::global()->bounded(1, 1000);
        arbol->Agregar(valor);
    }
    hayBusqueda = false;
    actualizarLienzo();
}

void MainWindow::onBotonCambiarGradoClic() {
    bool ok;
    int gradoNuevo = QInputDialog::getInt(this, "Cambiar grado del Árbol B",
                                          "Ingrese el grado nuevo (el árbol se reiniciará):",
                                          arbol->ObtenerGrado(), 3, 20, 1, &ok);
    if(!ok) return;
    delete arbol;
    arbol = new ArbolB<int>(gradoNuevo);
    hayBusqueda = false;
    actualizarLienzo();
}

// ---- Constantes de dibujo ----
static const int ALTO_CAJA = 30;
static const int SEPARACION_HORIZONTAL = 20;   // espacio mínimo entre subárboles vecinos
static const int SEPARACION_VERTICAL = 80;     // distancia entre niveles

// Calcula el ancho en píxeles que ocupa la caja de un nodo según sus claves
int MainWindow::anchoDeCaja(const ArbolB<int>::NodoVista &nodo) {
    QString textoClaves = "";
    for (size_t i = 0; i < nodo.claves.size(); i++) {
        textoClaves += QString::number(nodo.claves[i]);
        if (i < nodo.claves.size() - 1) textoClaves += " | ";
    }
    QGraphicsTextItem medidor(textoClaves);
    medidor.setFont(QFont("Arial", 12, QFont::Bold));
    return medidor.boundingRect().width() + 20;
}

// PASADA 1: calcula el ancho total que necesita el subárbol con raíz en 'nodo'.
// Una hoja necesita el ancho de su caja; un nodo interno necesita la suma de
// los anchos de sus hijos (más la separación entre ellos).
int MainWindow::calcularAnchoSubarbol(const ArbolB<int>::NodoVista &nodo) {
    if (nodo.esHoja) {
        return anchoDeCaja(nodo);
    }
    int suma = 0;
    for (size_t i = 0; i < nodo.hijos.size(); i++) {
        suma += calcularAnchoSubarbol(nodo.hijos[i]);
        if (i < nodo.hijos.size() - 1) suma += SEPARACION_HORIZONTAL;
    }
    // El nodo nunca ocupa menos que su propia caja
    return qMax(suma, anchoDeCaja(nodo));
}

void MainWindow::actualizarLienzo() {
    escena->clear();

    etiquetaInfo->setText(
        QString("Grado M: %1     |     Altura: %2     |     Total de claves: %3")
            .arg(arbol->ObtenerGrado())
            .arg(arbol->ObtenerAltura())
            .arg(arbol->ObtenerNumClaves())
    );

    if (!arbol->EstaVacia()) {
        ArbolB<int>::NodoVista vista = arbol->ExportarVista(hayBusqueda, claveBuscada);
        // El centro X del árbol se coloca en 0; la pasada 1 define el ancho total.
        dibujarNodoRecursivo(vista, 0, 0);
        // Ajustamos el rectángulo de la escena a su contenido, con un margen
        escena->setSceneRect(escena->itemsBoundingRect().adjusted(-50, -50, 50, 50));
    }
}

// PASADA 2: dibuja el nodo centrado en 'centroX' a la altura 'y', y reparte
// a cada hijo exactamente el ancho que necesita (calculado en la pasada 1).
void MainWindow::dibujarNodoRecursivo(const ArbolB<int>::NodoVista &nodo, int centroX, int y) {
    QString textoClaves = "";
    for (size_t i = 0; i < nodo.claves.size(); i++) {
        textoClaves += QString::number(nodo.claves[i]);
        if (i < nodo.claves.size() - 1) textoClaves += " | ";
    }

    QGraphicsTextItem *textoItem = new QGraphicsTextItem(textoClaves);
    textoItem->setDefaultTextColor(Qt::white);
    textoItem->setFont(QFont("Arial", 12, QFont::Bold));

    int anchoCaja = textoItem->boundingRect().width() + 20;

    QBrush relleno = nodo.resaltado ? QBrush(Qt::green) : QBrush(Qt::blue);
    escena->addRect(centroX - anchoCaja/2, y, anchoCaja, ALTO_CAJA, QPen(Qt::white, 2), relleno);

    textoItem->setPos(centroX - anchoCaja/2 + 10, y + 2);
    escena->addItem(textoItem);

    if (!nodo.esHoja) {
        // Ancho total que ocupan todos los hijos juntos
        int anchoTotalHijos = 0;
        std::vector<int> anchos;
        for (size_t i = 0; i < nodo.hijos.size(); i++) {
            int w = calcularAnchoSubarbol(nodo.hijos[i]);
            anchos.push_back(w);
            anchoTotalHijos += w;
            if (i < nodo.hijos.size() - 1) anchoTotalHijos += SEPARACION_HORIZONTAL;
        }

        // El borde izquierdo desde donde empezamos a colocar hijos
        int cursorX = centroX - anchoTotalHijos / 2;
        int hijoY = y + SEPARACION_VERTICAL;

        for (size_t i = 0; i < nodo.hijos.size(); i++) {
            // El centro de cada hijo está a la mitad de su propio ancho
            int hijoCentroX = cursorX + anchos[i] / 2;

            escena->addLine(centroX, y + ALTO_CAJA, hijoCentroX, hijoY, QPen(Qt::white, 2));
            dibujarNodoRecursivo(nodo.hijos[i], hijoCentroX, hijoY);

            cursorX += anchos[i] + SEPARACION_HORIZONTAL;
        }
    }
}
