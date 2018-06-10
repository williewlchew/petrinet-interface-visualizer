#include "events.h"

/*
 * Molecule
 */
Molecule::Molecule()
{
    name="New Molecule";
    input = true;
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
    input = inputInput;
}

bool Molecule::getInput(){
    return input;
}

/*
 * Events
 */

Events::Events()
{
    name = "";
}

Events::~Events()
{

}
