#include "mainwindow.h"
#include "area.h"
#include "inv.h"
#include "lookwindow.h"
#include "launchdialog.h"
#include "enddialog.h"
#include "start.h"

#include <QLabel>
#include <QKeyEvent>
#include <QIcon>
#include <cmath>
#include <QDebug>

int MainWindow::symbolCounter = ship::MAX_JOURNEYS;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("DOT");
    setMinimumSize(800,650); //minimum size allowed when resizing

    int w = this->width();
    int h = this->height();
    QPoint margins = QPoint(10,10);

    //tabs...
    tabs = new QTabWidget(this);
    tabs->setFixedSize(w - margins.x()*2, h - margins.y()*2);
    tabs->move(margins);
    tabs->setTabPosition(QTabWidget::South);
    tabs->setIconSize(QSize(60,60));
    tabs->setTabShape(QTabWidget::Triangular);
    tabs->setStyleSheet("QTabBar::tab {"
                        "height: 70px; width: 70px; border: none; margin: 2px; "
                        "padding-top: 0px; padding-bottom: 0px; padding-right: -8px }"
                        "QTabBar::tab:selected {"
                        "background-color: #B0C9CB;}");

    //end game button...
    endGameButton = new QPushButton(this);
    endGameButton->setText("END GAME");
    endGameButton->move(QPoint(w - endGameButton->width() - margins.y(), h - endGameButton->height() - margins.x()));
    endGameButton->setFont(QFont("Andale Mono",16));

    //three main tabs: the 'porthole', the ship's control, and the inventory
    areaPorthole = new area(tabs);
    testship = new ship(tabs);
    inventory = new inv(tabs);

    //QWIDGETS//
    porthole = areaPorthole;
    shipControl = testship;
    invWidget = inventory;

    tabs->addTab(porthole,QIcon(":/resources/seeIcon.png"),"");
    tabs->addTab(shipControl, QIcon(":/resources/seeIcon.png"),"");
    tabs->addTab(inventory, QIcon(":/resources/seeIcon.png"),"");

    //SET FIRST AREA / ISLAND
    areaManager *a = new areaManager(0);
    a->generateIsland();
    a->arriveAtIsland(areaPorthole);
    islands.push_back(a);
    onThisIsland = &islands.front();
    //---------------------//

    //CREATE AND DISPLAY THE 'START' DIALOG
    /*QDialog *startDialog = new Start(this);
    startDialog->setAttribute(Qt::WA_DeleteOnClose);
    //connect(ldialog, SIGNAL(destroyed(QObject*)), this, SIGNAL(lookDialogClosed()));
    startDialog->exec();*/

    connect(testship, SIGNAL(launchButtonReleased()), this, SLOT(handleLaunchClick()));
    connect(areaPorthole, SIGNAL(lookDialogClosed()), inventory, SLOT(handleLookWindowClosed()));
    connect(areaPorthole, SIGNAL(lookDialogClosed()), this, SLOT(handleLookWindowClosed()));
    connect(areaPorthole, SIGNAL(sectionButtonReleased(QAbstractButton*)), this, SLOT(handleSectionButton(QAbstractButton*)));
    connect(endGameButton, SIGNAL(released()), this, SLOT(handleEndGameButton()));
}

//incr can be -1 or +1 (change current tab)
int MainWindow::findTabIndex(int incr){
    int i = tabs->currentIndex() + incr;
    if (i == -1){
        return 0;
    } else if (i == tabs->count()){
        return tabs->count()-1;
    } else {
        return i;
    }

}

//take values in cbRecord, apply to SymbolBits
bool MainWindow::prepDestInfo(){

    if (testship->getCBRecord().size() != 5){
        return false;
    }

    int num = 0; //NOTE: MIN(num) = 31, MAX(num) = 496 (total options: 465)
    testship->getSymbolBits().fill(false); //clear symbolBits.
    for (int i = 0; i < 5; i++){
        testship->getSymbolBits().setBit(testship->getCBRecord()[i]);
        //manual conversion from bits to int
        num += pow(2, testship->getCBRecord()[i]);
    }
    if (testship->getCurrentSymbolID() != num){
        testship->setCurrentSymbolID(num);
        return true;
    } else {
        qDebug("You're already there.");
        return false;
    }
}

//----------------------------------------------------------------------------//
//------------------SLOTS (and key-release event handling)--------------------//
//----------------------------------------------------------------------------//

void MainWindow::keyReleaseEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Left){
        tabs->setCurrentIndex(findTabIndex(-1));
        return;
    } else if (event->key() == Qt::Key_Right){
        tabs->setCurrentIndex(findTabIndex(+1));
        return;
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

//One of two slots that handle the signal 'lookdialog closed'. This one updates the item list in the Section the user is at.
//The other is located in Inv.
void MainWindow::handleLookWindowClosed(){
    std::vector<item*> temp = (*onThisIsland)->updateItemRecord();
    if (temp.size() > 0){
        inventory->addItemObjects(temp);
    }
}


void MainWindow::handleLaunchClick(){
    qDebug("LAUNCH!");
    // 1. Check if destination was set, and if that destination is new (ie not the island you're on).
    bool destIsSet = prepDestInfo();

    bool endOfGameReached = (symbolCounter < 0);

    if (endOfGameReached){
        //END THE GAME HERE
        handleEndGameButton();
    }

    //-----final check------//
    if (destIsSet){
        qDebug("All systems go.");
        //----------//
        // a. Image -->
        QString imgPath = "//Users//mavis//QTprojects//dot//symbolStorage//temp_symbol.png";
        QImage test1(imgPath);
        QString symbolNum = QString::number(ship::MAX_JOURNEYS - symbolCounter);
        QString imgPathNew = "//Users//mavis//QTprojects//dot//symbolStorage//symbol" + symbolNum + ".png";
        test1.save(imgPathNew);

        // b. Display image in 'ship'
        testship->addSymbolLabel();
        symbolCounter--;
        testship->setProgressValue(symbolCounter);
        //----------//
        qDebug("Heading to the next island.");
        //-----------//
        // if we need to, make a new island.
        // a. check through all existing islands...
        bool islandExists = false;
        int symID = 0;
        for (islandsVecIt it = islands.begin(); it != islands.end(); it++){
            symID = (*it)->getSymbolID();

            if (symID == testship->getCurrentSymbolID()){
                //b. if it does exist, use existing island
                qDebug("Returning to an island.");
                islandExists = true;
                onThisIsland = &(*it);
                break;
            }
        }
        // c. if it doesn't exist, create a new island.
        if (!islandExists){
            qDebug("Creating a new island.");
            areaManager *a = new areaManager(testship->getCurrentSymbolID());
            a->generateIsland();
            islands.push_back(a);
            onThisIsland = &islands.back();

        }
        //display
        (*onThisIsland)->arriveAtIsland(areaPorthole);
        //-----------//
        qDebug("done.\n-----------");
    }

    //finally, open dialog. This will open even if you haven't set a dest, etc, but will tell you what you missed in that case.
    launchDialog *launchDetails = new launchDialog(this);
    QDialog *journeyDetails = launchDetails;
    journeyDetails->setAttribute(Qt::WA_DeleteOnClose);
    if (destIsSet){
        launchDetails->setDesc1((*onThisIsland)->getJourneyFullDesc());
        launchDetails->setDesc2((*onThisIsland)->getIslandFullDesc());
        connect(journeyDetails, SIGNAL(destroyed(QObject*)), this, SLOT(switchToPortholeTab()));
    } else {
        launchDetails->setDesc1("You can't set off without a destination in mind...");
        launchDetails->setDesc2("If you've set a destination, you're probably on that island already.");
    }
    journeyDetails->exec();
}

//SLOT
void MainWindow::switchToPortholeTab(){
    tabs->setCurrentIndex(0);
}


//1. get current island
//2. change section
void MainWindow::handleSectionButton(QAbstractButton * button){
    QString sectionName = button->objectName();
    if (sectionName == "islandCenterButton"){
        (*onThisIsland)->arriveAtSection(0, areaPorthole);
    } else if (sectionName == "northShoreButton"){
        (*onThisIsland)->arriveAtSection(1, areaPorthole);
    } else if (sectionName == "eastShoreButton"){
        (*onThisIsland)->arriveAtSection(2, areaPorthole);
    } else if (sectionName == "southShoreButton"){
        (*onThisIsland)->arriveAtSection(3, areaPorthole);
    } else {
        (*onThisIsland)->arriveAtSection(4, areaPorthole);
    }
}

void MainWindow::handleEndGameButton(){
    QDialog *theEnd = new endDialog(this);
    theEnd->setAttribute(Qt::WA_DeleteOnClose);
    theEnd->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    theEnd->move(QPoint(0,0));
    theEnd->exec();

    //DELETE.......


}

