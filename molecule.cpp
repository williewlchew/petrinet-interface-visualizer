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
    QString evName = QString::fromStdString(rootEvent->getName());
    painter.drawText(pix->rect(),Qt::AlignCenter, name);
    painter.end();

    //make it viewable
    QLabel* newLable = new QLabel(parent);
    newLabel->setPixmap(*pix);
    delete pix;
    newLable->show();

    return newLable;
}
