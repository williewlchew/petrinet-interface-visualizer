#include "molecule.h"
#include "visualeditor.h"
#include "attribute.h"

/////////////////////////////////////////////////////////////////

Molecule::Molecule()
{
    attributes = new AttributeList();

    Attribute* newName = new Attribute(Attribute::STRING, "name");
    newName->setData(std::string("New Molecule"));
    connect(newName, SIGNAL(VisualDataUpdated()), this, SLOT(updateMoleculeLabel()));

    Attribute* newColor = new Attribute(Attribute::COLOR, "color");
    newColor->setData(Qt::green);
    connect(newName, SIGNAL(VisualDataUpdated()), this, SLOT(updateMoleculeLabel()));

    attributes->Push(newName);
    attributes->Push(newColor);
}

Molecule::~Molecule()
{

}

//Name getter and setter
void Molecule::setName(std::string nameInput)
{
    attributes->Get("name")->setData(std::string(nameInput));
}

std::string Molecule::getName()
{
    return attributes->Get("name")->GetText();
}

QLabel* Molecule::DrawMolecule(QFrame* parent)
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(150,100);
    pix->fill(Qt::transparent);

    QPainter painter;
    painter.begin(pix);
    painter.setBrush(getColor());
    painter.drawEllipse(0,0,150,100);
    painter.drawText(pix->rect(),Qt::AlignCenter, QString::fromStdString(getName()));
    painter.end();

    //make it viewable
    QLabel* newLabel = new QLabel(parent);
    newLabel->setPixmap(*pix);
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    newLabel->setAttribute(Qt::WA_DeleteOnClose);
    newLabel->show();
    delete pix;

    label = newLabel;
    return newLabel;
}

void Molecule::EditMolecule(QFrame* parent)
{
    editor = new VisualEditor(parent, attributes);
}

void Molecule::updateMoleculeLabel()
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(150,100);//":/snip1.png");
    pix->fill(Qt::transparent);

    QPainter painter;
    painter.begin(pix);
    painter.setBrush(getColor());
    painter.drawEllipse(0,0,150,100);
    painter.drawText(pix->rect(),Qt::AlignCenter, QString::fromStdString(getName()));
    painter.end();

    label->setPixmap(*pix);
    label->show();
}

void Molecule::setColor(int input)
{
    QColor currentColor;

    //very temporary
    if(input == 0)
    {
        currentColor = Qt::white;
    }
    else if(input == 1)
    {
        currentColor = Qt::red;
    }
    else if(input == 2)
    {
        currentColor = Qt::blue;
    }
    else
    {
        currentColor = Qt::darkGreen;
    }

    attributes->Get("color")->setData(currentColor);
}

QColor Molecule::getColor()
{
    return attributes->Get("color")->GetColor();
}
