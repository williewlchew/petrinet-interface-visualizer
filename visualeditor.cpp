#include "visualeditor.h"
#include "ui_visualeditor.h"

VisualEditor::VisualEditor(QWidget *parent, Molecule* rootMol) : QDialog(parent), ui(new Ui::VisualEditor)
{
    //initialize variables
    nameField = "";
    rootMolecule = rootMol;

    ui->setupUi(this);
}

VisualEditor::~VisualEditor()
{
    delete ui;
}

//fill in form with molecule info
void VisualEditor::fillForm(){
    ui->MolNameEdit->setText(QString::fromStdString(rootMolecule->getName()));
}

QPushButton* VisualEditor::getSaveButton(){
    return ui->MolSaveButton;
}

void VisualEditor::on_MolSaveButton_clicked()
{
    rootMolecule->setName(nameField);
    changedId();
}

void VisualEditor::on_MolNameEdit_textEdited(const QString &arg1)
{
    nameField = arg1.toUtf8().constData();;
}
