////////////////////////////////////////////////////////////////////
#include "visualizer.h"
#include <QDebug>
///////////////////////////////////////////////////////////////////
Visualizer::Visualizer(QWidget *parent, Event* eventPtr): QFrame(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setMaximumSize(16777215, 16777215);

    layout = new QVBoxLayout;
    setLayout(layout);

    event = eventPtr;
    updateVisualizer();
}

Visualizer::~Visualizer()
{

}

void Visualizer::updateVisualizer()
{
    clearVisualizer();

    QBoxLayout* inputList = event->inputs.DrawMoleculeList(this);
    QLabel* eventLabel = event->DrawEvent(this);
    QBoxLayout* outputList = event->outputs.DrawMoleculeList(this);

    //move them to the optimal spots
    layout->addItem(inputList);
    layout->addWidget(eventLabel);
    layout->addItem(outputList);
}

void Visualizer::clearVisualizer()
{
    QLayoutItem* item;
    while ( ( item = layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

void Visualizer::mousePressEvent(QMouseEvent *QEvent)
{
    QLabel* child = static_cast<QLabel*>(childAt(QEvent->pos()));

    //mouse event on nothing
    if (!child)
    {
        return;
    }
//    FOR LATER
//    //rightclicked on an object
//    else if (event->button()==Qt::RightButton) {
//        if(!child->rootMolecule){
//            editEvent();
//        }
//        else{
//            editMolecule(child);
//            child->show();
//        }
//    }

    else
    {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << QPoint(QEvent->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("label/", itemData);

        QPixmap pixmap = *child->pixmap();
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QEvent->pos() - child->pos());

//        QPixmap tempPixmap = pixmap;
//        QPainter painter;
//        painter.begin(&tempPixmap);
//        painter.fillRect(pixmap.rect(), QColor(250, 250, 250, 150));
//        painter.end();

        //child->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
            child->close();
        else
        {
            child->show();
            child->setPixmap(pixmap);
        }
    }
}

void Visualizer::dragEnterEvent(QDragEnterEvent *QEvent)
{
    if (QEvent->mimeData()->hasFormat("label/")) {
        if (QEvent->source() == this) {
            QEvent->setDropAction(Qt::MoveAction);
            QEvent->accept();
        } else {
            QEvent->acceptProposedAction();
        }
    } else {
        QEvent->ignore();
    }
}

void Visualizer::dragMoveEvent(QDragMoveEvent *QEvent)
{
    if (QEvent->mimeData()->hasFormat("label/"))
    {
        if (QEvent->source() == this)
        {
            QEvent->setDropAction(Qt::MoveAction);
            QEvent->accept();
        }
        else
        {
            QEvent->acceptProposedAction();
        }
    }

    else
    {
        QEvent->ignore();
    }
}

void Visualizer::dropEvent(QDropEvent *QEvent)
{
    if (QEvent->mimeData()->hasFormat("label/"))
    {
        //extract info from event
        QByteArray itemData =QEvent->mimeData()->data("label/");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPoint startPosition;
        dataStream >> startPosition;

        event->processDragAction(startPosition, QEvent->pos() - startPosition, this);

        if (QEvent->source() == this)
        {
            QEvent->setDropAction(Qt::MoveAction);
            QEvent->accept();
         }

        else
        {
            QEvent->acceptProposedAction();
        }
    }

    else
    {
        QEvent->ignore();
    }
}
///////////////////////////////////////////////////////////////////
