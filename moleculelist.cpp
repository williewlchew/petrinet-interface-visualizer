#include "moleculelist.h"

MoleculeList::MoleculeList()
{

}

MoleculeList::~MoleculeList()
{

}

Molecule* MoleculeList::Get(std::string name)
{
    for(Molecule* i : list)
    {
        if(i->getName().compare(name) == 0)
        {
            return i;
        }
    }
    return nullptr;
}

Molecule* MoleculeList::Get(int index)
{
    return list[index];
}

void MoleculeList::Push(Molecule* item)
{
    list.push_back(item);
}

void MoleculeList::Pop(Molecule* item)
{
    int removeIndex = GetIndex(item);
    list.erase(list.begin() + removeIndex);
    delete item;
}

int MoleculeList::GetIndex(Molecule* item)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == item){
            return i;
        }
    }
    return -1;
}


QHBoxLayout* MoleculeList::DrawMoleculeList(QFrame* parent)
{
    QHBoxLayout* newLayout = new QHBoxLayout(parent);

    for(Molecule* mol : list)
    {
        QLabel* molLabel = mol->DrawMolecule(parent);
        newLayout->addWidget(molLabel);
    }

    return newLayout;

}

