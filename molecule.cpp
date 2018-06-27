#include "molecule.h"

Molecule::Molecule()
{
    attributes.push_back("New Molecule");
    attributes.push_back("blank");
}

Molecule::~Molecule()
{

}

//Name getter and setter
void Molecule::setName(std::string nameInput)
{
    attributes[0] = nameInput;
}

std::string Molecule::getName()
{
    return attributes[0];
}

QLabel* Molecule::DrawMolecule(QFrame* parent)
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(150,100);//":/snip1.png");
    pix->fill(Qt::transparent);
    //*pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    QPainter painter;
    painter.begin(pix);
    painter.drawEllipse(0,0,150,100);
    painter.drawText(pix->rect(),Qt::AlignCenter, QString::fromStdString(attributes[0]));
    painter.end();

    //make it viewable
    QLabel* newLabel = new QLabel(parent);
    newLabel->setPixmap(*pix);
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    newLabel->setAttribute(Qt::WA_DeleteOnClose);
    newLabel->show();
    delete pix;

    return newLabel;
}

void Molecule::EditMolecule(QFrame* parent)
{
    editor = new VisualEditor(parent, attributes);
    connect(*editor->saveButton, SIGNAL(released()), this, SLOT(updateMolecule()));
}

void Molecule::updateMolecule()
{
    attributes = editor->data;
    Changed();
}
