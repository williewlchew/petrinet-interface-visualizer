#include "event.h"
#include <QDebug>

Event::Event()
{
    attributes = new AttributeList();

    Attribute* newName = new Attribute(Attribute::STRING, "name");
    newName->setData(std::string("New Event"));
    connect(newName, SIGNAL(VisualDataUpdated()), this, SLOT(updateEventLabel()));

    Attribute* newColor = new Attribute(Attribute::COLOR, "color");
    newColor->setData(Qt::green);
    connect(newName, SIGNAL(VisualDataUpdated()), this, SLOT(updateEventLabel()));

    attributes->Push(newName);
    attributes->Push(newColor);
}

Event::~Event()
{

}

void Event::setName(std::string nameInput)
{
    attributes->Get("name")->setData(std::string(nameInput));
}

std::string Event::getName()
{
    return attributes->Get("name")->GetText();
}

QLabel* Event::DrawEvent(QFrame* parent)
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(150,100);
    pix->fill(Qt::transparent);

    QPainter painter;
    painter.begin(pix);
    painter.setBrush(Qt::green);
    painter.drawRect(0,0,150,100);
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

void Event::updateEventLabel()
{
    //load the image into a pixmap
    QPixmap* pix = new QPixmap(150,100);
    pix->fill(Qt::transparent);

    QPainter painter;
    painter.begin(pix);
    painter.setBrush(Qt::green);
    painter.drawRect(0,0,150,100);
    painter.drawText(pix->rect(),Qt::AlignCenter, QString::fromStdString(getName()));
    painter.end();

    label->setPixmap(*pix);
    label->show();
}

std::vector<QPoint*> Event::getMolLabelPoints()
{
    std::vector<QPoint*> ret = inputs.GetLabelPoints();
    std::vector<QPoint*> add = outputs.GetLabelPoints();
    ret.insert(std::end(ret), std::begin(add), std::end(add));

    return ret;
}

void Event::Edit(QFrame* parent){
    editor = new VisualEditor(parent, attributes);
}

void Event::processDragAction(QLabel* startPtr, QPoint endPoint, QFrame* parent)
{
      if(startPtr->pos().y() < parent->frameRect().height()/2 && endPoint.y() < parent->frameRect().height()/2)
      {
          //movement in input
          inputs.Move(startPtr, endPoint);
      }

      else if(startPtr->pos().y() < parent->frameRect().height()/2 && endPoint.y() > parent->frameRect().height()/2)
      {
          //input to output
          int destination = outputs.PositionToVector(endPoint);
          outputs.Insert(inputs.Get(startPtr), destination);
          inputs.Pop(startPtr);
      }

      else if(startPtr->pos().y() > parent->frameRect().height()/2 && endPoint.y() < parent->frameRect().height()/2)
      {
          //output to input
          int destination = inputs.PositionToVector(endPoint);
          inputs.Insert(outputs.Get(startPtr), destination);
          outputs.Pop(startPtr);
      }

      else if(startPtr->pos().y() > parent->frameRect().height()/2 && endPoint.y() > parent->frameRect().height()/2)
      {
          //movement in output
          outputs.Move(startPtr, endPoint);
      }

      inputs.DrawMoleculeList();
      outputs.DrawMoleculeList();
}
