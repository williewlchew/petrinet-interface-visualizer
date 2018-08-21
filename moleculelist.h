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

class MoleculeList : public QObject
{
    public:
        //Constructor
        MoleculeList();
        ~MoleculeList();

        //Getters
        Molecule* Get(std::string name);
        Molecule* Get(QLabel* item);
        Molecule* Get(int index);
        std::vector<QPoint*> GetLabelPoints();

        //Manipulation Methdods
        void Push(Molecule* item);
        void Push(Molecule* item, bool isInput);
        void Pop(Molecule* item);

        bool IsIn(QLabel* item);
        bool IsIn(Molecule* item);

        //When label is moved in visualizer
        void Pop(QLabel* item);
        void Insert(Molecule* item, int position);
        void Move(QLabel* item, QPoint position);

        //Visual
        QHBoxLayout* DrawMoleculeList(QFrame* parent);
        int PositionToVector(QPoint position);
        bool Edit(QLabel* label, QFrame* parent);

   Q_OBJECT
   public slots:
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
        void ClearLabelList();
};

#endif // MOLECULELIST_H
