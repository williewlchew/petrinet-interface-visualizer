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
      if(startPtr->pos().y() < parent->frameRect().height()/2 && endPoint.y() < parent->frameRect().height()/2)
      {
          //movement in input
          qDebug() << "1";
          inputs.Move(startPtr, endPoint);
      }

      else if(startPtr->pos().y() < parent->frameRect().height()/2 && endPoint.y() > parent->frameRect().height()/2)
      {
          //input to output
          qDebug() << "2";
          int destination = outputs.PositionToVector(endPoint);
          outputs.Insert(inputs.Get(startPtr), destination);
          inputs.Pop(startPtr);
      }

      else if(startPtr->pos().y() > parent->frameRect().height()/2 && endPoint.y() < parent->frameRect().height()/2)
      {
          //output to input
          qDebug() << "3";
          int destination = inputs.PositionToVector(endPoint);
          inputs.Insert(outputs.Get(startPtr), destination);
          outputs.Pop(startPtr);
      }

      else if(startPtr->pos().y() > parent->frameRect().height()/2 && endPoint.y() > parent->frameRect().height()/2)
      {
          //movement in output
          qDebug() << startPtr->pos().y() << " " <<  parent->frameRect().y()/2;
          outputs.Move(startPtr, endPoint);
      }

//    if(inputs.IsIn(startPtr))
//    {
//        inputs.Move(startPtr, endPoint);
//    }
      inputs.DrawMoleculeList();
      outputs.DrawMoleculeList();
}
