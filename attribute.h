#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <QtWidgets>
#include <QObject>

class Attribute : public QObject
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
        void Display(QDialog* parent, QBoxLayout* layout, std::vector<std::string> fieldValues);

        void setData(std::string input);
        void setData(QColor input);

    Q_OBJECT
    signals:
        void VisualDataUpdated();

    public slots:
        void editedAttribute();

    private:
        //Base data
        std::string name;
        type attributeType;

        //Data
        std::string data;
        QColor* colorData;

        QLineEdit* field;

};

#endif // ATTRIBUTE_H
