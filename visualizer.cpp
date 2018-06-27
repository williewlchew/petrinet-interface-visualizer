////////////////////////////////////////////////////////////////////
#include "visualizer.h"
#include <QDebug>
///////////////////////////////////////////////////////////////////
Visualizer::Visualizer(QWidget *parent, Event* eventPtr): QFrame(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setMaximumSize(16777215, 16777215);
    setAcceptDrops(true);

    layout = new QVBoxLayout;
    setLayout(layout);

    event = eventPtr;

    inputList = event->inputs.DrawMoleculeList(this);
    layout->addItem(inputList);
    eventLabel = event->DrawEvent(this);
    layout->addWidget(eventLabel);
    outputList = event->outputs.DrawMoleculeList(this);
    layout->addItem(outputList);
}

Visualizer::~Visualizer()
{

}

void Visualizer::updateVisualizer()
{

}

void Visualizer::clearVisualizer()
{

}

void Visualizer::mousePressEvent(QMouseEvent *QEvent)
{
    QLabel* child = static_cast<QLabel*>(childAt(QEvent->pos()));

    //mouse event on nothing
    if (!child)
    {
        return;
    }

    //rightclicked on an object
    else if (QEvent->button()==Qt::RightButton) {
        if(!event->inputs.Edit(child,this))
        {
            if(!event->outputs.Edit(child,this))
            {
                event->Edit(this);
            }
        }
    }

    else
    {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << QPoint(QEvent->pos());

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
            //child->close();
            qDebug() << "boof";
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

        QLabel* labPtr = static_cast<QLabel*>(childAt(startPosition));
        event->processDragAction(labPtr, QEvent->pos(), this);

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
