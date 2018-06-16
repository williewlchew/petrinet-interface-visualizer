////////////////////////////////////////////////////////////////////
/*
 * Molecule object:
 *  -Stores base data and attributes of a molecule
 *  -Has methods of how to draw the molecule
 *  -Has methods on encoding and decoding the molecule
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
        QLabel* DrawMolecule(QWidget* parent);

    private:
       //Base Data
       std::string name;


};

#endif // MOLECULE_H
