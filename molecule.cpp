#include "molecule.h"

Molecule::Molecule()
{
    name="New Molecule";
}

Molecule::~Molecule()
{

}

//Name getter and setter
void Molecule::setName(std::string nameInput)
{
    name = nameInput;
}

std::string Molecule::getName()
{
    return name;
}

//
void Molecule::DrawMolecule(q){
    /* OLD CODE
     *
     */
}
