#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <QtWidgets>


class Attribute
{
    public:
        enum type {STRING, COLOR};

        //Constructors
        Attribute(type typeInput, std::string nameInput);
        virtual ~Attribute();

        //Getters and Setters
        std::string GetName();
        type GetType();
        std::string GetText();
        QColor GetColor();

        //visual
        QHBoxLayout Display(QDialog* parent, QBoxLayout* layout, std::vector<std::string> fieldValues);

   public slots:
        void setTextData(std::string stringInput);
        void setColorData(QColor colorInput);


    private:
        //Base data
        std::string name;
        type attributeType;

        //Data
        std::string stringData;
        QColor* colorData;

};

#endif // ATTRIBUTE_H
