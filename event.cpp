#include "event.h"

Event::Event()
{
    name = "New Event";
}

Event::~Event()
{

}

void Event::setName(std::string nameInput)
{
    name = nameInput;
}

std::string Event::getName()
{
    return name;
}

QLabel* Event::DrawEvent(QFrame* parent)
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(":/snip2.png");
    *pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    QPainter painter;
    painter.begin(pix);
    painter.drawText(pix->rect(),Qt::AlignCenter,QString::fromStdString(name));
    painter.end();

    //make it viewable
    QLabel* newLabel = new QLabel(parent);
    newLabel->setPixmap(*pix);
    delete pix;
    newLabel->move(parent->width()/2 - 75, parent->height()/2 - 50);
    newLabel->show();
    newLabel->setAttribute(Qt::WA_DeleteOnClose);

    return newLabel;
}

void Event::editEvent(QFrame* parent){

//    //***OPTIMIZE FOR EVENTS

//    //makes a second dialogbox
//    VisualEditor* newEditor = new VisualEditor(parent);
//    newEditor->fillForm();//fill in the box with current information
//    newEditor->show();

//    //connect the save button with updateMolecule() ****WIP
//    connect(newEditor, SIGNAL(changedId()), parent, SLOT(updateEvent()));
}
