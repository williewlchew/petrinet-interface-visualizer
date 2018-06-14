////////////////////////////////////////////////////////////////////
/*
 * Molecule object:
 *  base data : name
 *  will have : AttributeList, encode/decode methods
 */
////////////////////////////////////////////////////////////////////
#ifndef MOLECULE_H
#define MOLECULE_H

#include <iostream>
#include <QtWidgets>

////////////////////////////////////////////////////////////////////
class Molecule
{
    public:
        //Constructors
        Molecule();
        ~Molecule();

        //Name Methods
        void setName(std::string nameInput);
        std::string getName();

        //Visual
        void DrawMolecule(QWidget* parent);

    private:
       //Base Data
       std::string name;


};

#endif // MOLECULE_H
