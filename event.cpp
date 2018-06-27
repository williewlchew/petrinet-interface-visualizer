#include "event.h"
#include <QDebug>

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
    newLabel->setAlignment(Qt::AlignCenter);
    newLabel->setAttribute(Qt::WA_DeleteOnClose);
    newLabel->show();

    return newLabel;
}

void Event::Edit(QFrame* parent){

//    editor = new VisualEditor(parent);
//    editor->fillForm(this);
}

void Event::processDragAction(QLabel* startPtr, QPoint endPoint, QFrame* parent)
{
    if(inputs.IsIn(startPtr))
    {
        inputs.Move(startPtr, endPoint);
    }
}
