#include "lookwindow.h"
#include "ui_lookwindow.h"
#include <QDebug>

//initialize static variable.
QString lookWindow::descOfItems = "Nothing.";
std::vector<QString> lookWindow::itemNames = {};
std::vector<QString> lookWindow::takenItemNames = {};

lookWindow::lookWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lookWindow)
{
    ui->setupUi(this);
    ui->descLabel->setText(descOfItems);

    for (int i = 0; i < itemNames.size(); i++){
        ui->takeItemBox->addItem(itemNames[i]);
    }

    connect(ui->closeButton, SIGNAL(released()), this, SLOT (close()));
    connect(ui->takeButton, SIGNAL(released()), this, SLOT(handleTakeButton()));

}

lookWindow::~lookWindow()
{
    delete ui;
}

void lookWindow::handleTakeButton(){
    qDebug("TAKE!");
    QString nameOfItem = ui->takeItemBox->currentText();
    int takeIndex = ui->takeItemBox->currentIndex();
    if (nameOfItem != ""){
        qDebug() << "Adding: " << nameOfItem;
        //1. add to 'takenItemNames' vector
        takenItemNames.push_back(nameOfItem);
        //2. remove from 'itemNames' vector
        itemNames.erase( itemNames.begin()  + takeIndex);
        //3. remove from ui takeItemBox
        ui->takeItemBox->removeItem(takeIndex);
    }
}

