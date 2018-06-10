#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "events.h"

/*
 * Constructors and destructor
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //testing
    Events* newEv = new Events();
    //testing

    newVisualizer = new Visualizer(this, newEv);
    ui->dragFrame->addWidget(newVisualizer);
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
    newVisualizer->newMolecule();
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
