#include "attribute.h"
#include "QDebug"

Attribute::Attribute(type typeInput, std::string nameInput) : QObject(nullptr)
{
    attributeType = typeInput;
    name = nameInput;
    field = nullptr;
    data = "";

    switch(attributeType)
    {
        case COLOR:
            colorData = new QColor;
            break;
        default:
        case STRING:
            colorData = nullptr;
            break;
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
    return data;
}

QColor Attribute::GetColor()
{
    if(attributeType == COLOR)
        return *colorData;
    else return Qt::white;
}

void Attribute::setData(std::string input)
{
    data = input;
    if(attributeType == COLOR)
    {
        colorData->setNamedColor(QString::fromStdString(data));
    }
}

void Attribute::setData(QColor colorInput)
{
        if(attributeType == COLOR)
            *colorData = colorInput;
}

void Attribute::editedAttribute()
{
    data = field->text().toUtf8().constData();
    if(attributeType == COLOR)
    {
        colorData->setNamedColor(QString::fromStdString(data));
    }

    if(name.compare("name") == 0 || name.compare("color") == 0)
    {
        VisualDataUpdated();
    }
}

void Attribute::Display(QDialog *parent, QBoxLayout* layout, std::vector<std::string> fieldValues)
{
    //Make the name label
    QLabel* nameLab = new QLabel(parent);
    nameLab->setText(QString::fromStdString(name));

    //Get the field value for the VisualEditor in a line editor
    QLineEdit* newField = new QLineEdit(parent);
    std::string value;
    if(attributeType == STRING)
        value = GetText();
        else if(attributeType == COLOR)
        value = colorData->name().toUtf8().constData();
    newField->setText(QString::fromStdString(value));

    //connect line edit with change
    field = newField;
    QObject::connect(field, SIGNAL(editingFinished()),this, SLOT(editedAttribute()));

    //Group name label and line edit together
    QHBoxLayout* newGroup = new QHBoxLayout;
    newGroup->addWidget(nameLab);
    newGroup->addWidget(field);

    //Add to the new dialog window
    layout->addItem(newGroup);
    fieldValues.push_back(value);
}

