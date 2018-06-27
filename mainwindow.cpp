#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventlist.h"

/*
 * Constructors and destructor
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //CODE BELOW IS IN ITS CURRENT STATE FOR TESTING PURPOSES
    EventList* eventList = new EventList();
    eventList->Push(new Event());
    eventList->Get(0)->inputs.Push(new Molecule);    eventList->Get(0)->inputs.Get(0)->setName("InputMolecule1");
    eventList->Get(0)->inputs.Push(new Molecule);    eventList->Get(0)->inputs.Get(1)->setName("InputMolecule2");
    eventList->Get(0)->inputs.Push(new Molecule);    eventList->Get(0)->inputs.Get(2)->setName("InputMolecule3");
    eventList->Get(0)->outputs.Push(new Molecule);   eventList->Get(0)->outputs.Get(0)->setName("OutputMolecule");

    visualizer = new Visualizer(this, eventList->Get(0));
    ui->dragFrame->addWidget(visualizer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Slot and signals
 */
void MainWindow::on_addStateButton_clicked()
{
    //AddState();
    //visualizer->newMolecule();
}

/*
 * Functions
 */

//adds a new state to the list
void MainWindow::AddState()
{
    QListWidgetItem *NewListItem = new QListWidgetItem("New State");
    NewListItem->setFlags(NewListItem->flags() | Qt::ItemIsEditable);
    ui->mainList->addItem(NewListItem);
}
