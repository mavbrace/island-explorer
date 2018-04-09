#include "area.h"
#include "ui_area.h"
#include "lookwindow.h"

#include <QDialog>
#include <QDebug>
#include <QPixmap>

//AREA: an island.

//CONSTANT
//desolate, mountainous/treed, inhabited/abandoned, grassy/hill
//images organized in that order, with 5 images per zone (at the moment ... later, will add more for variety)
//orgnaized like: [middle], [<coast>a], [<coast>b], [<coast>c], [<coast>d]. The last four are interchangeable (TODO).
const std::array<QString, 20> area::outsideImages = {"scene00.png","scene00a.png","scene00b.png","scene00c.png","scene00d.png",
                                                    "scene03.png","scene03a.png","scene03b.png","scene03c.png","scene03d.png",
                                                    "scene01.png","scene01a.png","scene01b.png","scene01c.png","scene01d.png",
                                                    "scene02.png","scene02a.png","scene02b.png","scene02c.png","scene02d.png",
                                                   };

area::area(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::area)
{   
    ui->setupUi(this);

    takenItemsTemp = {}; //initialize

    //connect the button to the right slot...
    connect(ui->lookButton, SIGNAL(released()), this, SLOT (handleLookButton()));
    connect(ui->mapButtons, SIGNAL(buttonReleased(QAbstractButton*)), this, SIGNAL(sectionButtonReleased(QAbstractButton*)));
}

area::~area()
{
    delete ui;
}

//TODO: make this for whichSection as well
void area::setOutsideImage(int whichZone, int whichSection){
    //whichZone = what 'row', whichSection = what 'column'
    QString imgFile = ":/resources/";
    imgFile.append(outsideImages[(whichZone*5) + whichSection]);
    QPixmap p = QPixmap(imgFile);
    qDebug() << imgFile;
    ui->outside->setPixmap(p);
}

void area::setSectionMarker(int whichSection){
    if (whichSection == 0){
        ui->xLabel->setGeometry(ui->islandCenterButton->geometry());
    } else if (whichSection == 1){
        ui->xLabel->setGeometry(ui->northShoreButton->geometry());
    } else if (whichSection == 2){
        ui->xLabel->setGeometry(ui->eastShoreButton->geometry());
    } else if (whichSection == 3){
        ui->xLabel->setGeometry(ui->southShoreButton->geometry());
    } else {
        ui->xLabel->setGeometry(ui->westShoreButton->geometry());
    }
}

void area::handleLookButton(){
    QDialog *ldialog = new lookWindow(this);
    ldialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(ldialog, SIGNAL(destroyed(QObject*)), this, SIGNAL(lookDialogClosed()));
    ldialog->exec();
}








