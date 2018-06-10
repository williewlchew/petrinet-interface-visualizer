#include "visualizer.h"
#include "events.h"

#include <QDebug>

/*
 * VisualMolecule
 */

VisualMolecule::VisualMolecule(QWidget *parent, Molecule* root): QLabel(parent)
{
    rootMolecule = root;
    updateMolecule();
}

VisualMolecule::~VisualMolecule(){

}

Molecule* VisualMolecule::getRoot(){
    return rootMolecule;
}

void VisualMolecule::updateMolecule(){

    //load the image into a pixmap
    QPixmap* pix = new QPixmap(":/TFsnip.png");
    *pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    QPainter painter;
    painter.begin(pix);
    QString molName = QString::fromStdString(rootMolecule->getName());
    painter.drawText(pix->rect(),Qt::AlignCenter, molName);
    painter.end();

    //make it viewable
    this->setPixmap(*pix);
    delete pix;
    this->show();
}


/*
 * Visualizer
 */
Visualizer::Visualizer(QWidget *parent, Events* eventPtr) : QFrame(parent)
{
    //initialize
    draggedMolecule = nullptr;
    //setup widget
    setMinimumSize(500, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    rootEvent = eventPtr;
    /*
     * loop through inputs
     *      create visuals for each
     * loop though outputs
     *      visuals for each
     */
}

Visualizer::~Visualizer(){

}

  //Visualizer Drag Event Handling

void Visualizer::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("molecule/")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Visualizer::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("molecule/")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Visualizer::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("molecule/")) {
        //extract info from event
        QByteArray itemData = event->mimeData()->data("molecule/");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        Molecule* rootMol = draggedMolecule;

        //make new molecule in dropped position
        VisualMolecule* newMol = newMolecule(rootMol);
        newMol->move(event->pos() - offset);
        newMol->show();

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Visualizer::mousePressEvent(QMouseEvent *event)
{
    VisualMolecule* child = static_cast<VisualMolecule*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    /**
        construct a QByteArray and package up the details using a QDataStream
            itemData is an array of bytes
            the stream puts pixmap information into item data
            stored in event's mime data
    **/
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    draggedMolecule = child->getRoot();
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("molecule/", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(250, 250, 250, 150));
    painter.end();

    child->setPixmap(tempPixmap);

    if (event->button()==Qt::RightButton) {
        editMolecule(child);
        child->show();
        child->setPixmap(pixmap);
    }

    else if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    }

    else {
        child->show();
        child->setPixmap(pixmap);
    }
}

  // Functions
//make a new molecule
VisualMolecule* Visualizer::newMolecule(){

    /*
     * make a new molecule in the events object
     * make a new visual molecule that corresponds with the new molecule
     */

    Molecule* newMol = new Molecule();
    rootEvent->inputs.push_back(newMol);
    VisualMolecule *visualMol = new VisualMolecule(this, newMol);
    visualMol->setAttribute(Qt::WA_DeleteOnClose);

    //temp
    visualMol->move(100,100);
    visualMol->show();

    return visualMol;
}

VisualMolecule* Visualizer::newMolecule(Molecule* molPtr){

    VisualMolecule *visualMol = new VisualMolecule(this, molPtr);
    visualMol->setAttribute(Qt::WA_DeleteOnClose);

    //temp
    visualMol->move(100,100);
    visualMol->show();

    return visualMol;
}

//load up a window to edit the selected molecule
void Visualizer::editMolecule(VisualMolecule* visualMol){

    //makes a second dialogbox
    VisualEditor* newEditor = new VisualEditor(this, visualMol->getRoot());
    newEditor->fillForm();//fill in the box with current information
    newEditor->show();

    //connect the save button with updateMolecule()
    connect(newEditor, SIGNAL(changedId()), visualMol, SLOT(updateMolecule()));
}
