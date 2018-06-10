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
        VisualMolecule(QWidget* parent, Molecule* root); //builds the molecule based on code put in the name; look for ','
        virtual ~VisualMolecule();

        //getter
        Molecule* getRoot();

    private:
        //attributes
        Molecule* rootMolecule;

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

    //constructor
    Visualizer();
    Visualizer(QWidget *parent = nullptr, Events* eventPtr = nullptr);
    virtual ~Visualizer();

    //methods
    VisualMolecule* newMolecule();
    VisualMolecule* newMolecule(Molecule* mol);

private:

    //attributes
    Molecule* draggedMolecule;

    //methods
    void editMolecule(VisualMolecule* mol);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H
