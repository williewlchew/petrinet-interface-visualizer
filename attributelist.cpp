#include "attributelist.h"

AttributeList::AttributeList()
{

}

AttributeList::~AttributeList()
{

}

Attribute* AttributeList::Get(std::string name)
{
    for(Attribute* i : list)
    {
        if(i->GetName().compare(name) == 0)
        {
            return i;
        }
    }
    return nullptr;
}

void AttributeList::Push(Attribute *item)
{
    list.push_back(item);
}

void AttributeList::Display(QDialog *parent, QBoxLayout* layout, std::vector<std::string> fieldValues)
{
    for(Attribute* i : list)
    {
        i->Display(parent, layout, fieldValues);
    }
}
