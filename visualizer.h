////////////////////////////////////////////////////////////
/*
 * The Visualizer
 *  -canvas in which the objects draw themselves on
 *  -sets up where each object should draw themselves
 *  -responsible for drawing lines
 */
////////////////////////////////////////////////////////////
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtWidgets>
#include <QFrame>

#include "visualeditor.h"
#include "event.h"

///////////////////////////////////////////////////////////
class Visualizer : public QFrame
{
    public:
        //constructor
        Visualizer(QWidget *parent = nullptr, Event* eventPtr = nullptr);
        virtual ~Visualizer();

    private:
        Event* event;
        QVBoxLayout *layout;

        //helper methods
        void clearVisualizer();

    public slots:
        void updateVisualizer();
};
////////////////////////////////////////////////////////////
//// OLD CODE
//class VisualMolecule : public QLabel {
//    Q_OBJECT

//    public :
//        //constuctors
//        VisualMolecule(QWidget* parent);
//        VisualMolecule(QWidget* parent, Molecule* root);
//        virtual ~VisualMolecule();

//        //getter
//        Molecule* getRoot();
//        void setIsMovable(bool moveInput);
//        bool getIsMoveable();

//    private:
//        //attributes
//        Molecule* rootMolecule;
//        bool isMovable;

//    public slots:
//        void updateMolecule();
//};

//class QDragEnterEvent;
//class QDropEvent;

//class Visualizer : public QFrame
//{
//public:

//    //attributes
//    Events* rootEvent; //~used to read in the molecules
//    VisualMolecule* visualEvent;

//    //constructor
//    Visualizer();
//    Visualizer(QWidget *parent = nullptr, Events* eventPtr = nullptr);
//    virtual ~Visualizer();

//    //methods
//    VisualMolecule* newMolecule();
//    VisualMolecule* newMolecule(Molecule* mol);
//    void LoadNewEvent(Events* newEvent);

//private:

//    //attributes
//    Molecule* draggedMolecule;

//    //methods
//    void editMolecule(VisualMolecule* mol);
//    void editEvent();
//    void updateEvent();

//protected:
//    void dragEnterEvent(QDragEnterEvent *event) override;
//    void dragMoveEvent(QDragMoveEvent *event) override;
//    void dropEvent(QDropEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//};

#endif //VISUALIZER_H
