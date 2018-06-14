#ifndef MOLECULELIST_H
#define MOLECULELIST_H

#include <vector>
#include "molecule.h"

class MoleculeList
{

    public:
        //Constructor
        MoleculeList();
        ~MoleculeList();

        //Manipulation Methdods
        Molecule* Get(std::string name);
        Molecule* Get(int index);
        void Push(Molecule* item);
        void Pop(Molecule* item);

        //Visual
        QLabel* DrawMoleculeList(QWidget* parent);

   private:
        //Base Data
        std::vector<Molecule*> list;
};

#endif // MOLECULELIST_H
