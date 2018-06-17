////////////////////////////////////////////////////////////////////
#include "visualizer.h"
#include <QDebug>
///////////////////////////////////////////////////////////////////
Visualizer::Visualizer(QWidget *parent, Event* eventPtr)
{
    event = eventPtr;
    updateVisualizer();
}

Visualizer::~Visualizer()
{

}

void Visualizer::updateVisualizer()
{
    QBoxLayout* inputList = event->inputs.DrawMoleculeList(this);
    QLabel* eventLabel = event->DrawEvent(this);
    QBoxLayout* outputList = event->outputs.DrawMoleculeList(this);

    //move them to the optimal spots
}
///////////////////////////////////////////////////////////////////
/// OLD CODE

//Visualizer::Visualizer(QWidget *parent) : QFrame(parent)
//{
//    //setup widget
//    setMinimumSize(500, 200);
//    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
//    setAcceptDrops(true);
//}

//Visualizer::~Visualizer(){

//}

//void Visualizer::mousePressEvent(QMouseEvent *event)
//{
//    QLabel* child = static_cast<QLabel*>(childAt(event->pos()));

//    //mouse event on nothing
//    if (!child)
//        return;

//    //rightclicked on an object
//    else if (event->button()==Qt::RightButton) {
//        if(!child->getRoot()){
//            editEvent();
//        }
//        else{
//            editMolecule(child);
//            child->show();
//        }
//    }

//    //drag event
//    else if (child->getIsMoveable()){
//        QPixmap pixmap = *child->pixmap();

//        QByteArray itemData;
//        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//        dataStream << pixmap << QPoint(event->pos() - child->pos());

//        QMimeData *mimeData = new QMimeData;
//        mimeData->setData("label/", itemData);

//        QDrag *drag = new QDrag(this);
//        drag->setMimeData(mimeData);
//        drag->setPixmap(pixmap);
//        drag->setHotSpot(event->pos() - child->pos());

//        QPixmap tempPixmap = pixmap;
//        QPainter painter;
//        painter.begin(&tempPixmap);
//        painter.fillRect(pixmap.rect(), QColor(250, 250, 250, 150));
//        painter.end();

//        child->setPixmap(tempPixmap);

//        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
//            child->close();
//        else {
//            child->show();
//            child->setPixmap(pixmap);
//        }
//    }
//}

//void Visualizer::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasFormat("label/")) {
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
//}

//void Visualizer::dragMoveEvent(QDragMoveEvent *event)
//{
//    if (event->mimeData()->hasFormat("label/")) {
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
//}

//void Visualizer::dropEvent(QDropEvent *event)
//{
//    if (event->mimeData()->hasFormat("label/")) {
//        //extract info from event
//        QByteArray itemData = event->mimeData()->data("label/");
//        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//        QPixmap pixmap;
//        QPoint offset;
//        dataStream >> pixmap >> offset;

//        /*
//         * Tell object to draw themselves in new area
//         */
//}
///*
// * OLD CODE
// */

//VisualMolecule::VisualMolecule(QWidget *parent): QLabel(parent)
//{
//    rootMolecule = nullptr;
//}

//VisualMolecule::VisualMolecule(QWidget *parent, Molecule* root): QLabel(parent)
//{
//    rootMolecule = root;
//    updateMolecule();
//}

//VisualMolecule::~VisualMolecule(){

//}

//Molecule* VisualMolecule::getRoot(){
//    return rootMolecule;
//}

//void VisualMolecule::updateMolecule(){

//    //initialize variable
//    isMovable = true;

//    //load the image into a pixmap
//    QPixmap* pix = new QPixmap(":/snip1.png");
//    *pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

//    QPainter painter;
//    painter.begin(pix);
//    QString molName = QString::fromStdString(rootMolecule->getName());
//    painter.drawText(pix->rect(),Qt::AlignCenter, molName);
//    painter.end();

//    //make it viewable
//    this->setPixmap(*pix);
//    delete pix;
//    this->show();
//}

//void VisualMolecule::setIsMovable(bool moveInput)
//{
//    isMovable = moveInput;
//}

//bool VisualMolecule::getIsMoveable(){
//    return isMovable;
//}


///*
// * Visualizer
// */
//Visualizer::Visualizer(QWidget *parent, Events* eventPtr) : QFrame(parent)
//{
//    //initialize
//    draggedMolecule = nullptr;

//    //setup widget
//    setMinimumSize(500, 200);
//    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
//    setAcceptDrops(true);

//    LoadNewEvent(eventPtr);
//}

//Visualizer::~Visualizer(){

//}

//  //Visualizer Drag Event Handling

//void Visualizer::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasFormat("molecule/")) {
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
//}

//void Visualizer::dragMoveEvent(QDragMoveEvent *event)
//{
//    if (event->mimeData()->hasFormat("molecule/")) {
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
//}

//void Visualizer::dropEvent(QDropEvent *event)
//{
//    if (event->mimeData()->hasFormat("molecule/")) {
//        //extract info from event
//        QByteArray itemData = event->mimeData()->data("molecule/");
//        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//        QPixmap pixmap;
//        QPoint offset;
//        dataStream >> pixmap >> offset;
//        Molecule* rootMol = draggedMolecule;

//        //make new molecule in dropped position
//        VisualMolecule* newMol = newMolecule(rootMol);
//        newMol->move(event->pos() - offset);
//        newMol->show();

//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
//}

//void Visualizer::mousePressEvent(QMouseEvent *event)
//{
//    VisualMolecule* child = static_cast<VisualMolecule*>(childAt(event->pos()));

//    //mouse event on nothing
//    if (!child)
//        return;

//    //rightclicked on an object
//    else if (event->button()==Qt::RightButton) {
//        if(!child->getRoot()){
//            editEvent();
//        }
//        else{
//            editMolecule(child);
//            child->show();
//        }
//    }

//    //drag event
//    else if (child->getIsMoveable()){
//        /**
//            construct a QByteArray and package up the details using a QDataStream
//                itemData is an array of bytes
//                the stream puts pixmap information into item data
//                stored in event's mime data
//        **/
//        QPixmap pixmap = *child->pixmap();

//        QByteArray itemData;
//        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//        draggedMolecule = child->getRoot();
//        dataStream << pixmap << QPoint(event->pos() - child->pos());

//        QMimeData *mimeData = new QMimeData;
//        mimeData->setData("molecule/", itemData);

//        QDrag *drag = new QDrag(this);
//        drag->setMimeData(mimeData);
//        drag->setPixmap(pixmap);
//        drag->setHotSpot(event->pos() - child->pos());

//        QPixmap tempPixmap = pixmap;
//        QPainter painter;
//        painter.begin(&tempPixmap);
//        painter.fillRect(pixmap.rect(), QColor(250, 250, 250, 150));
//        painter.end();

//        child->setPixmap(tempPixmap);

//        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
//            child->close();
//        else {
//            child->show();
//            child->setPixmap(pixmap);
//        }
//    }
//}

//  // Functions
//void Visualizer::LoadNewEvent(Events* newEvent){
//    /*
//     * Make a new event structure
//     * set it as the current event
//     */

//    rootEvent = newEvent;
//    /* Read in the event:
//     *  loop through molecules
//     *      create visuals for each
//     */

//    //make the event object
//    visualEvent = new VisualMolecule(this);
//    visualEvent->setIsMovable(false);
//    visualEvent->setAttribute(Qt::WA_DeleteOnClose);
//    updateEvent();
//}

////update the visual representation of the event
//void Visualizer::updateEvent(){

//    //load the image into a pixmap
//    QPixmap* pix = new QPixmap(":/snip2.png");
//    *pix = pix->scaled(150, 100, Qt::IgnoreAspectRatio, Qt::FastTransformation);

//    QPainter painter;
//    painter.begin(pix);
//    QString evName = QString::fromStdString(rootEvent->getName());
//    painter.drawText(pix->rect(),Qt::AlignCenter, evName);
//    painter.end();

//    //make it viewable
//    visualEvent->setPixmap(*pix);
//    delete pix;
//    visualEvent->move(this->width()/2 - 75, this->width()/2 - 50);
//    visualEvent->show();
//}

//void Visualizer::editEvent(){

//    //***OPTIMIZE FOR EVENTS

//    //makes a second dialogbox
//    VisualEditor* newEditor = new VisualEditor(this);
//    newEditor->fillForm();//fill in the box with current information
//    newEditor->show();

//    //connect the save button with updateMolecule()
//    connect(newEditor, SIGNAL(changedId()), this, SLOT(updateEvent()));
//}

////make a new molecule
//VisualMolecule* Visualizer::newMolecule(){

//    /*
//     * make a new molecule in the events object
//     * make a new visual molecule that corresponds with the new molecule
//     */

//    Molecule* newMol = new Molecule();
//    rootEvent->molecules.push_back(newMol);
//    VisualMolecule *visualMol = new VisualMolecule(this, newMol);
//    visualMol->setAttribute(Qt::WA_DeleteOnClose);

//    //temp
//    visualMol->move(100,100);
//    visualMol->show();

//    return visualMol;
//}

//VisualMolecule* Visualizer::newMolecule(Molecule* molPtr){

//    VisualMolecule *visualMol = new VisualMolecule(this, molPtr);
//    visualMol->setAttribute(Qt::WA_DeleteOnClose);

//    //temp
//    visualMol->move(100,100);
//    visualMol->show();

//    return visualMol;
//}

////load up a window to edit the selected molecule
//void Visualizer::editMolecule(VisualMolecule* visualMol){

//    //makes a second dialogbox
//    VisualEditor* newEditor = new VisualEditor(this, visualMol->getRoot());
//    newEditor->fillForm();//fill in the box with current information
//    newEditor->show();

//    //connect the save button with updateMolecule()
//    connect(newEditor, SIGNAL(changedId()), visualMol, SLOT(updateMolecule()));
//}
