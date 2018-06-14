#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <moleculelist.h>

class Event
{
    public:
        //Constructor
        Event();
        ~Event();

        //Name Methods
        void setName(std::string nameInput);
        std::string getName();

        //Visual
        QLabel* DrawEvent(QWidget* parent);

    private:
        std::string name;
};

#endif // EVENT_H
