//////////////////////////////////////////////
/*
 * Visual Editor
 *  -lets users interact with object attributes
 *  -tells objects which attribute to change
 */
//////////////////////////////////////////////
#ifndef VISUALEDITOR_H
#define VISUALEDITOR_H

#include <QDialog>
#include <QtWidgets>
#include <iostream>
#include <vector>

//////////////////////////////////////////////
namespace Ui {
class VisualEditor;
}

class VisualEditor : public QDialog
{
    Q_OBJECT

    public:

        //Attributes
        std::string nameField;

        //constructors
        VisualEditor(QWidget *parent, std::vector<std::string> incomingData);
        virtual ~VisualEditor();

        void fillForm();
        std::vector<std::string> data;
        QPushButton* saveButton;


    private:
        QVBoxLayout* layout;
        std::vector<std::string> fieldValues;
        void AddField(std::string name, std::string value);

        Ui::VisualEditor *ui;
};

#endif // VISUALEDITOR_H
