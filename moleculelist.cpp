#include "moleculelist.h"

MoleculeList::MoleculeList()
{

}

MoleculeList::MoleculeList()
{

}

Molecule* Get(std::string name)
{
    for(Event* i : list)
    {
        if(i->getName().compare(name) == 0)
        {
            return i;
        }
    }
}

Molecule* Get(int index)
{
    return list[index];
}

void Push(Molecule* item)
{
    list.push_back(item);
}

void Pop(Molecule* item)
{
    int removeIndex = GetIndex(item);
    list.erase(list.begin() + removeIndex);
    delete item;
}

int GetIndex(Molecule* item)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == item){
            return i;
        }
    }
}


QHBoxLayout* DrawMoleculeList(QFrame* parent)
{
    QHBoxLayout* newLayout = new QHBoxLayout(parent);

    for(Molecule* mol : list)
    {
        QLabel molLabel = mol->DrawMolecule(newLayout);
        newLayout->addWidget(molLabel);
    }

    return newLayout;

}

