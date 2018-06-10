#ifndef VISUALEDITOR_H
#define VISUALEDITOR_H

#include <QDialog>
#include "events.h"

namespace Ui {
class VisualEditor;
}

class VisualEditor : public QDialog
{
    Q_OBJECT

public:

    //Attributes
    Molecule* rootMolecule;
    std::string nameField;

    //constructors
    VisualEditor(QWidget *parent = 0, Molecule* rootMol = nullptr);
    ~VisualEditor();

    void fillForm();
    QPushButton* getSaveButton();

signals:
    void changedId();

private slots:
    void on_MolSaveButton_clicked();

    void on_MolNameEdit_textEdited(const QString &arg1);

private:
    Ui::VisualEditor *ui;
};

#endif // VISUALEDITOR_H
