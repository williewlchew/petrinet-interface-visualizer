//////////////////////////////////////////////////////////////////////////////
/// Molecule List
///     -Has the container of the list of molecules
///     -Has methods on how to manipulate the list
///     -Coordinates drawing the list of molecules
///     -Can encode/decode a sequnce of molecules
//////////////////////////////////////////////////////////////////////////////
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
        QLayout* DrawMoleculeList(QWidget* parent);

   private:
        //Base Data
        std::vector<Molecule*> list;

        //Helpers
        int GetIndex(Molecule* item);

};

#endif // MOLECULELIST_H
