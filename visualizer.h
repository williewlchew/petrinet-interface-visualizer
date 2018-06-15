////////////////////////////////////////////////////////////
/*
 * The Visualizer
 *  -canvas in which the objects draw themselves on
 *  -proceses mouse events and relays the event data to the respective objects
 *  -know how to accesss any object that it represents
 */
////////////////////////////////////////////////////////////
#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QtWidgets>
#include <QFrame>

#include "visualeditor.h"
#include "events.h"

class VisualMolecule : public QLabel {
    Q_OBJECT

    public :
        //constuctors
        VisualMolecule(QWidget* parent);
        VisualMolecule(QWidget* parent, Molecule* root);
        virtual ~VisualMolecule();

        //getter
        Molecule* getRoot();
        void setIsMovable(bool moveInput);
        bool getIsMoveable();

    private:
        //attributes
        Molecule* rootMolecule;
        bool isMovable;

    public slots:
        void updateMolecule();
};

class QDragEnterEvent;
class QDropEvent;

class Visualizer : public QFrame
{
public:

    //attributes
    Events* rootEvent; //~used to read in the molecules
    VisualMolecule* visualEvent;

    //constructor
    Visualizer();
    Visualizer(QWidget *parent = nullptr, Events* eventPtr = nullptr);
    virtual ~Visualizer();

    //methods
    VisualMolecule* newMolecule();
    VisualMolecule* newMolecule(Molecule* mol);
    void LoadNewEvent(Events* newEvent);

private:

    //attributes
    Molecule* draggedMolecule;

    //methods
    void editMolecule(VisualMolecule* mol);
    void editEvent();
    void updateEvent();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H
