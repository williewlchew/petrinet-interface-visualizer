#include "events.h"

/*
 * Molecule
 */
Molecule::Molecule()
{
    name="New Molecule";
    isInput = true;
}

Molecule::~Molecule()
{

}

void Molecule::setName(std::string nameInput){
    name = nameInput;
}

std::string Molecule::getName(){
    return name;
}

void Molecule::setInput(bool inputInput){
    isInput = inputInput;
}

bool Molecule::getInput(){
    return isInput;
}

/*
 * Events
 */

Events::Events()
{
    name = "New Event";
}

Events::~Events()
{

}

void Events::setName(std::string nameInput){
    name = nameInput;
}

std::string Events::getName(){
    return name;
}
