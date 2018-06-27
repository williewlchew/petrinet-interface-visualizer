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
/////////////////////////////////////////////////////
class Event
{
    public:
        //Constructor
        Event();
        ~Event();

        
        //Base Data
        MoleculeList inputs;
        MoleculeList outputs;
        
        void setName(std::string nameInput);
        std::string getName();

        //Visual
        QLabel* DrawEvent(QFrame* parent);
        void Edit(QFrame* parent);
        void processDragAction(QLabel* startPtr, QPoint endPoint, QFrame* parent);

        
    private:
        //Base Data
        std::string name;

        VisualEditor* editor;

};

#endif // EVENT_H
