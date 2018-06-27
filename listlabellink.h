#ifndef LISTLABELLINK_H
#define LISTLABELLINK_H

#include <vector>
#include "molecule.h"
#include "QtWidgets"


class ListLabelLink
{
    public:
        ListLabelLink();
        virtual ~ListLabelLink();

        void Add(Molecule* molPtr, QLabel* labPtr);
        void Remove(Molecule* molPtr);
        void Remove(QLabel* labPtr);

        Molecule* GetMol(QLabel* labPtr);
        QLabel* GetLabel(Molecule* molPtr);

    private:
        std::vector<Molecule*> molecules;
        std::vector<QLabel*> labels;
};

#endif // LISTLABELLINK_H
