#include "visualeditor.h"
#include "ui_visualeditor.h"

/*
 * Edits a molecule
 */
VisualEditor::VisualEditor(QWidget *parent, AttributeList *incomingData) : QDialog(parent), ui(new Ui::VisualEditor)
{
    //initialize variables
    layout = new QVBoxLayout(this);
    setLayout(layout);
    attributes = incomingData;

    fillForm();
    ui->setupUi(this);

    this->show();
}

VisualEditor::~VisualEditor()
{
    delete ui;
}

//fill in form with molecule info
void VisualEditor::fillForm(){
    //temporary
//    AddField("name" , data[0]);
//    AddField("color", data[1]);
    attributes->Display(this, layout, fieldValues);

    QPushButton* button = new QPushButton(this);
    button->setText("Save");
    saveButton = button;
    layout->addWidget(button);
}

//void VisualEditor::on_MolSaveButton_clicked()
//{
//    rootMolecule->setName(nameField);
//    changedId();
//}

//void VisualEditor::on_MolNameEdit_textEdited(const QString &arg1)
//{
//    nameField = arg1.toUtf8().constData();;
//}

void VisualEditor::AddField(std::string name, std::string value)
{
    QLabel* nameLab = new QLabel(this);
    nameLab->setText(QString::fromStdString(name));
    QLineEdit* field = new QLineEdit(this);
    field->setText(QString::fromStdString(value));
    QHBoxLayout* newGroup = new QHBoxLayout;
    newGroup->addWidget(nameLab);
    newGroup->addWidget(field);

    layout->addItem(newGroup);
    fieldValues.push_back(value);
}
