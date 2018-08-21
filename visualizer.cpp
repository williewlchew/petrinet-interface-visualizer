////////////////////////////////////////////////////////////////////
#include "visualizer.h"
#include <QDebug>

///////////////////////////////////////////////////////////////////
Visualizer::Visualizer(QWidget *parent, Event* eventPtr): QFrame(parent)
{
    //initialize frame
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setMaximumSize(16777215, 16777215);

    //initialize edition fuctionalities
    setAcceptDrops(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));

    //initialize helper variables
    event = eventPtr;
    menuPoint = QPoint();

    //initalize visualizer scene
    layout = new QVBoxLayout;
    setLayout(layout);

    inputList = event->inputs.DrawMoleculeList(this);
    layout->addLayout(inputList);
    eventLabel = event->DrawEvent(this);
    layout->addWidget(eventLabel);
    outputList = event->outputs.DrawMoleculeList(this);
    layout->addLayout(outputList);

    DrawLines();
}

Visualizer::~Visualizer()
{

}

void Visualizer::EditAction()
{
    if(!event->inputs.Edit(menuTempChild,this))
    {
        if(!event->outputs.Edit(menuTempChild,this))
        {
            event->Edit(this);
        }
    }
}

void Visualizer::CopyAction()
{
    menuClipboard = menuTempChild;
}

void Visualizer::CutAction()
{
    CopyAction();
    DeleteAction();
}

void Visualizer::DeleteAction()
{
    if(event->inputs.IsIn(menuTempChild))
    {
        event->inputs.Pop(menuTempChild);
        event->inputs.DrawMoleculeList();
    }
    else if(event->outputs.IsIn(menuTempChild))
    {
        event->outputs.Pop(menuTempChild);
        event->outputs.DrawMoleculeList();
    }
}

void Visualizer::AddAction()
{
    Molecule* newMolecule = new Molecule();
    menuTempChild = newMolecule->DrawMolecule(this);

    if(menuPoint.y() < frameRect().height()/2)
    {
        event->inputs.Push(newMolecule);
        event->inputs.DrawMoleculeList();
    }
    else if(menuPoint.y() > frameRect().height()/2)
    {
        event->outputs.Push(newMolecule);
        event->outputs.DrawMoleculeList();
    }

    EditAction();
}

void Visualizer::SaveAction()
{

}

void Visualizer::DrawLines()
{
    linePoints = event->getMolLabelPoints();
    //qDebug() << event->label->pos().x() << " " << event->label->pos().y();
    update();
}

void Visualizer::paintEvent(QPaintEvent* QEvent)
{
    QPainter paint(this);
    paint.setPen(Qt::black);
    for(QPoint* p : linePoints)
    {
        paint.drawLine(event->label->pos(),*p);
    }
    paint.end();
    QFrame::paintEvent(QEvent);
}

void Visualizer::ShowContextMenu(const QPoint &pos, QLabel* child)
{
   QMenu contextMenu(tr("Context menu"), this);

   menuTempChild = child;
   menuPoint.setX(pos.x()); menuPoint.setY(pos.y());

   QAction action1("Edit", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(EditAction()));
   contextMenu.addAction(&action1);
   QAction action2("Cut", this);
   connect(&action2, SIGNAL(triggered()), this, SLOT(CutAction()));
   contextMenu.addAction(&action2);
   QAction action3("Copy", this);
   connect(&action3, SIGNAL(triggered()), this, SLOT(CopyAction()));
   contextMenu.addAction(&action3);
   QAction action4("Delete", this);
   connect(&action4, SIGNAL(triggered()), this, SLOT(DeleteAction()));
   contextMenu.addAction(&action4);
   QAction action5("Add", this);
   connect(&action5, SIGNAL(triggered()), this, SLOT(AddAction()));
   contextMenu.addAction(&action5);
   QAction action6("Save", this);
   connect(&action6, SIGNAL(triggered()), this, SLOT(SaveAction()));
   contextMenu.addAction(&action6);

   contextMenu.exec(mapToGlobal(pos));
}

void Visualizer::mousePressEvent(QMouseEvent *QEvent)
{
    QLabel* child = static_cast<QLabel*>(childAt(QEvent->pos()));

    if (!child && QEvent->button()==Qt::RightButton)
    {
        ShowContextMenu(QEvent->pos(), nullptr);
    }

    else if(child && QEvent->button()==Qt::RightButton)
    {
        ShowContextMenu(QEvent->pos(), child);
    }

    else if(!child || child == event->label)
    {
        DrawLines();
        return;
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

        //child->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
            //child->close();
            qDebug() << "";
        else
        {
            child->show();
            child->setPixmap(pixmap);
        }
    }

    DrawLines();
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
