#include "inv.h"
#include "ui_inv.h"
#include "lookwindow.h"
#include "mainwindow.h"

#include <qDebug>

typedef std::vector<QString>::iterator vecIt;

inv::inv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inv)
{

    itemObjects.reserve(200); //40 locations (ie journeys, or islands) x 5 sections x 10 max objects = 2000.

    warningDefaultMsg = "Your inventory.";

    ui->setupUi(this);

    ui->itemsList->setStyleSheet( "QListWidget {"
                                  "background-color: grey;"
                                  "border-color: white;"
                                  "}"
                                  "QListWidget::item {background-color: white;"
                                  "border-style: solid;"
                                  "border-width: 5px;"
                                  "}"
                                  "QListWidget::item:selected {background-color: #768990;"
                                  "}" );


    connect(ui->tossButton, SIGNAL(released()), this, SLOT(handleTossButton()));
    connect(ui->eatButton, SIGNAL(released()), this, SLOT(handleEatButton()));
    connect(ui->burnButton, SIGNAL(released()), this, SLOT(handleBurnButton()));

}

inv::~inv()
{
    delete ui;
}


//One of two slots that handle the signal 'lookdialog closed'. This one updates the inventory based on the items the user has taken.
//The other one is located in MainWindow.
void inv::handleLookWindowClosed(){
    //1. add any 'taken' items to inventory. Name goes to the ui's itemlist, item object goes to a separate vector.
    for (vecIt it = lookWindow::takenItemNames.begin(); it != lookWindow::takenItemNames.end(); it++){
        QListWidgetItem  *item = new QListWidgetItem(*it);
        //---set icon---
        QString symbolNum = QString::number(ship::MAX_JOURNEYS - MainWindow::symbolCounter-1);
        QString imgPath = "//Users//mavis//QTprojects//dot//symbolStorage//symbol" + symbolNum + ".png";
        item->setIcon(QIcon(imgPath));
        ui->itemsList->addItem(item);
    }
    // NOTE: clearing out the 'takenItemNames' now happens in 'Sections'.

}

void inv::addItemObjects(std::vector<item*> addedItems){
    itemObjects.insert( itemObjects.end(), addedItems.begin(), addedItems.end() );
}

//----SLOTS-----//

void inv::handleTossButton(){
    // 1. delete that item from anywhere it exists. It can't be retrieved.

    //a. set warningLabel back to its normal message
    ui->warningLabel->setText(warningDefaultMsg);
    //b. check if the user has actually selected an item
    int row = ui->itemsList->currentRow();
    if (row != -1){
        removeItemFully(row);

    } else {
        ui->warningLabel->setText("What would you like to toss overboard, exactly?");
    }

}

void inv::handleEatButton(){
    //a. set warningLabel back to its normal message
    ui->warningLabel->setText(warningDefaultMsg);
    //b. check if the user has actually selected an item
    int row = ui->itemsList->currentRow();
    if (row != -1){
        qDebug("Eating...");
        int index = getItemIndexFromName(ui->itemsList->currentItem()->text());
        if (itemObjects[index]->isEdible()){
            removeItemFully(row);
            ui->warningLabel->setText("Delicious.");
        } else {
            ui->warningLabel->setText("You won't eat that.");
        }
    } else {
        ui->warningLabel->setText("What would you like to eat, exactly?");
    }
}

void inv::handleBurnButton(){
    //a. set warningLabel back to its normal message
    ui->warningLabel->setText(warningDefaultMsg);
    //b. check if the user has actually selected an item
    int row = ui->itemsList->currentRow();
    if (row != -1){
        qDebug("Burning...");
        int index = getItemIndexFromName(ui->itemsList->currentItem()->text());
        if (itemObjects[index]->isBurnable()){
            removeItemFully(row);
            ui->warningLabel->setText("You set the item on fire. It burns nicely.");
        } else {
            ui->warningLabel->setText("You attempt to set the item on fire. It doesn't catch.");
        }
    } else {
        ui->warningLabel->setText("What would you like to burn, exactly?");
    }

}

// -------end of SLOTS --------//

int inv::getItemIndexFromName(QString name){
    for (int i = 0; i < itemObjects.size(); i++){
        if (itemObjects.at(i)->getName() == name){
            return i;
        }
    }
    qDebug("Warning: Item was not found in itemObjects vector.");
}

//note: this remove the first instance of that name. Error could occur if the user did not choose the first instance,
//though this might only occur later (after further development).
void inv::removeFromItemObjects(QString name){
    for (int i = 0; i < itemObjects.size(); i++){
        if (itemObjects.at(i)->getName() == name){
            //remove first instance of that name.
            itemObjects.erase(itemObjects.begin() + i); //not using an iterator in this case, so this is how to do it.
            return;
        }
    }
    qDebug("Warning: Item was not found in itemObjects vector.");
}


void inv::removeItemFully(int row){
    //1. remove from ui->itemsList
    QString itemName = ui->itemsList->currentItem()->text();
    qDebug() <<"Getting rid of the " << itemName << ".";
    QListWidgetItem *item = ui->itemsList->takeItem(row);
    delete item;

    //2. itemObjects (have to do it by name)
    removeFromItemObjects(itemName);
}





