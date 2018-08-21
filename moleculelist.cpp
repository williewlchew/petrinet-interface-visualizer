#include "moleculelist.h"

MoleculeList::MoleculeList()
{
    visualLayout = nullptr;
    currentParent = nullptr;
}

MoleculeList::~MoleculeList()
{
    qDebug() << "Delete buggg";
}

/*
 * Manipulation Methods
 */

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

Molecule* MoleculeList::Get(QLabel* item)
{
    int index = GetIndex(item);
    if(index != -1)
        return list[index];
    else return nullptr;
}

Molecule* MoleculeList::Get(int index)
{
    return list[index];
}

std::vector<QPoint*> MoleculeList::GetLabelPoints()
{
    std::vector<QPoint*> ret;
    for(QLabel* lab : labels)
    {
        QPoint* point = new QPoint(lab->pos().y(), lab->pos().x());
        ret.push_back(point);
    }
    return ret;
}

void MoleculeList::Push(Molecule* item)
{
    list.push_back(item);
    if(item->label)
    {
        labels.push_back(item->label);
    }
}

void MoleculeList::Push(Molecule* item, bool isInput)
{
    list.push_back(item);
    if(isInput)
        item->setColor(1);
    else if(!isInput)
    {
        item->setColor(2);
    }
}

void MoleculeList::Pop(Molecule* item)
{
    int removeIndex = GetIndex(item);
    list.erase(list.begin() + removeIndex);
}

void MoleculeList::Pop(QLabel* item)
{
    int removeIndex = GetIndex(item);
    list.erase(list.begin() + removeIndex);
}

/*
 * User Input
 */

void MoleculeList::Insert(Molecule* item, int position)
{
    list.insert(list.begin() + position, item);
}

bool MoleculeList::Edit(QLabel* label, QFrame *parent)
{
    int index = GetIndex(label);
    if(index != -1)
    {
        list[index]->EditMolecule(parent);
        return true;
    }
    else return false;

}

bool MoleculeList::IsIn(QLabel* item)
{
    for(QLabel* lab : labels)
    {
        if(lab == item)
            return true;
    }

    return false;
}

bool MoleculeList::IsIn(Molecule* item)
{
    for(Molecule* mol : list)
    {
        if(mol == item)
            return true;
    }

    return false;
}

void MoleculeList::Move(QLabel* item, QPoint position)
{
    int moveIndex = GetIndex(item);
    int destinationIndex = PositionToVector(position);
    if(moveIndex != destinationIndex)
    {
        list.insert(list.begin() + destinationIndex, list[moveIndex]);
        if(moveIndex > destinationIndex)
            list.erase(list.begin() + moveIndex + 1);
        else list.erase(list.begin() + moveIndex);
    }
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

int MoleculeList::GetIndex(QLabel* item)
{
    for(int i = 0; i < labels.size(); i++)
    {
        if(labels[i] == item){
            return i;
        }
    }
    return -1;
}

int MoleculeList::PositionToVector(QPoint position)
{
    if(position.x() <= labels[0]->pos().x())
        return 0;

    for(int i = 0; i < list.size() - 1; i++)
    {
        if(position.x() >= labels[i]->pos().x() &&
           position.x() <= labels[i + 1]->pos().x())
        {
            return i;
        }
    }
    return (list.size() - 1);
}

/*
 * Visual
 */

QHBoxLayout* MoleculeList::DrawMoleculeList(QFrame* parent)
{
    visualLayout = new QHBoxLayout(parent);
    currentParent = parent;

    ClearLabelList();

    for(Molecule* mol : list)
    {
        QLabel* molLabel = mol->DrawMolecule(parent);
        labels.push_back(molLabel);
        visualLayout->addWidget(molLabel);
    }

    return visualLayout;
}

QHBoxLayout* MoleculeList::DrawMoleculeList()
{
    ClearLabelList();

    for(Molecule* mol : list)
    {
        QLabel* molLabel = mol->DrawMolecule(currentParent);
        labels.push_back(molLabel);
        visualLayout->addWidget(molLabel);
    }

    return visualLayout;
}

void MoleculeList::ClearLabelList()
{
    for(QLabel* lab : labels)
    {
        delete lab;
    }
    labels.clear();
}

