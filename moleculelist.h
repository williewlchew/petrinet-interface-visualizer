//////////////////////////////////////////////////////////////////////////////
/// Molecule List
///     -Has the container of the list of molecules
///         -Has methods on how to manipulate the list
///     -Coordinates drawing the list of molecules
///     -Can encode/decode a sequnce of molecules
//////////////////////////////////////////////////////////////////////////////
#ifndef MOLECULELIST_H
#define MOLECULELIST_H

#include <vector>
#include "molecule.h"
//#include "listlabellink.h"

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

        bool IsIn(QLabel* item);

        //When label is moved in visualizer
        void Pop(QLabel* item);
        void Insert(QLabel* item, QPoint position);
        void Move(QLabel* item, QPoint position);

        //Visual
        QHBoxLayout* DrawMoleculeList(QFrame* parent);
        bool Edit(QLabel* label, QFrame* parent);

   private slots:
        QHBoxLayout* DrawMoleculeList();

   private:
        //Base Data
        std::vector<Molecule*> list;
        std::vector<QLabel*> labels;

        //Visual
        QHBoxLayout* visualLayout;
        QFrame* currentParent;

        //Manipulation Helpers
        int GetIndex(Molecule* item);
        int GetIndex(QLabel* item);

        //Visual Helpers
        //ListLabelLink* LLLink;
        int PositionToVector(QPoint position);
        void ClearLabelList();
};

#endif // MOLECULELIST_H
