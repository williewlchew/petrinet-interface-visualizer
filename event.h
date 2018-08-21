///////////////////////////////////////////
/// Event Object:
///     -Has base data on event
///         -accessors to the lists of molecules
///     -Has attributes
///     -Can encode and decode an event
///////////////////////////////////////////
#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <moleculelist.h>
#include <QObject>
/////////////////////////////////////////////////////
class Event : public QObject
{
    Q_OBJECT

    public:
        //Constructor
        Event();
        ~Event();
        
        //Base Data
        MoleculeList inputs;
        MoleculeList outputs;

        //Getters and Setters
        void setName(std::string nameInput);
        std::string getName();
        std::vector<QPoint*> getMolLabelPoints();

        //Visual
        QLabel* label;

        QLabel* DrawEvent(QFrame* parent);
        void Edit(QFrame* parent);
        void processDragAction(QLabel* startPtr, QPoint endPoint, QFrame* parent);

        //Context menu variables
        Molecule* menuMolecule;
        QPoint* menuPosition;

    private slots:
        void updateEventLabel();
        
    private:
        //Base Data
        AttributeList* attributes;

        VisualEditor* editor;

};

#endif // EVENT_H
