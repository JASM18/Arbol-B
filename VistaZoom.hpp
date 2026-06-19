#ifndef VISTAZOOM_HPP
#define VISTAZOOM_HPP

#include <QGraphicsView>
#include <QWheelEvent>

// QGraphicsView personalizado que permite hacer zoom con la rueda del mouse.
// Se subclasea porque el zoom requiere sobrescribir el manejo del evento de
// la rueda (wheelEvent), cosa que no se puede hacer en un QGraphicsView normal.
class VistaZoom : public QGraphicsView {
    Q_OBJECT
public:
    explicit VistaZoom(QGraphicsScene *escena, QWidget *parent = nullptr)
        : QGraphicsView(escena, parent)
    {
        // El zoom se centra en la posicion del cursor, no en el centro de la vista
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent *evento) override {
        const double factorZoom = 1.15;
        if (evento->angleDelta().y() > 0) {
            scale(factorZoom, factorZoom);      // rueda hacia arriba -> acercar
        } else {
            scale(1.0 / factorZoom, 1.0 / factorZoom);  // hacia abajo -> alejar
        }
    }
};

#endif // VISTAZOOM_HPP
