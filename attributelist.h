#ifndef ATTRIBUTELIST_H
#define ATTRIBUTELIST_H

#include "attribute.h"
#include <vector>

class AttributeList
{
    public:
        AttributeList();
        virtual ~AttributeList();

        Attribute* Get(std::string name);
        void Push(Attribute* item);
        void Pop(Attribute* item);

        //visual
        void Display(QDialog* parent, QBoxLayout* layout, std::vector<std::string> fieldValues);

    private:
        std::vector<Attribute*> list;


};

#endif // ATTRIBUTELIST_H
