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
        void editEvent(QFrame* parent);
        void processDragAction(QPoint startPoint, QPoint endPoint, QFrame* parent);

        
    private:
        //Base Data
        std::string name;

        //Visual Helpers

};

#endif // EVENT_H
