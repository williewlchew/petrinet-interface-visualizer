#include "molecule.h"

Molecule::Molecule()
{
    name="New Molecule";
}

Molecule::~Molecule()
{

}

//Name getter and setter
void Molecule::setName(std::string nameInput)
{
    name = nameInput;
}

std::string Molecule::getName()
{
    return name;
}

QLabel* Molecule::DrawMolecule(QFrame* parent)
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(":/snip1.png");
    *pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    QPainter painter;
    painter.begin(pix);
    painter.drawText(pix->rect(),Qt::AlignCenter, QString::fromStdString(name));
    painter.end();

    //make it viewable
    QLabel* newLabel = new QLabel(parent);
    newLabel->setPixmap(*pix);
    delete pix;
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setAttribute(Qt::WA_DeleteOnClose);
    newLabel->show();

    return newLabel;
}
