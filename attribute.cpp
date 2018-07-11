#include "attribute.h"
#include "QDebug"

Attribute::Attribute(type typeInput, std::string nameInput)
{
    attributeType = typeInput;
    name = nameInput;

    switch(attributeType)
    {
        case STRING:
            stringData = "";
            colorData = nullptr;
        case COLOR:
            stringData = "";
            colorData = new QColor;
    }
}

Attribute::~Attribute()
{

}

std::string Attribute::GetName()
{
    return name;
}

Attribute::type Attribute::GetType()
{
    return attributeType;
}

std::string Attribute::GetText()
{
    return "";//stringData;
}

QColor Attribute::GetColor()
{
    if(attributeType == COLOR && colorData)
    {
        return *colorData;
    }
    else return "";
}

void Attribute::setTextData(std::string stringInput)
{
    stringData = stringInput;
}

void Attribute::setColorData(QColor colorInput)
{
    if(attributeType == COLOR)
        *colorData = colorInput;
}

QHBoxLayout Attribute::Display(QDialog *parent, QBoxLayout* layout, std::vector<std::string> fieldValues)
{
    QLabel* nameLab = new QLabel(parent);
    nameLab->setText(QString::fromStdString(name));

    QLineEdit* field = new QLineEdit(parent);
    std::string value;
    if(attributeType == STRING)
    {
        value = GetText();
    }
    else if(attributeType == COLOR)
    {
        value = colorData->name().toUtf8().constData();
    }
    field->setText(QString::fromStdString(value));

    QHBoxLayout* newGroup = new QHBoxLayout;
    newGroup->addWidget(nameLab);
    newGroup->addWidget(field);

    layout->addItem(newGroup);
    fieldValues.push_back(value);
}

