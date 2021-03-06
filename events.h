#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <Vector>

class Molecule
{
    public:
        //constructors
        Molecule();
        ~Molecule();

        //getters and setters
        void setName(std::string nameInput);
        std::string getName();
        void setInput(bool inputInput);
        bool getInput();


    private:
       //attributes
       std::string name;
       bool isInput;

       //other stuff
};

class Events
{
    public:
        //constructors
        Events();
        ~Events();

        //getters and setters
        void setName(std::string nameInput);
        std::string getName();

        //attributes
        std::vector<Molecule*> molecules;

    private:
        std::string name;
};

#endif // EVENT_H
