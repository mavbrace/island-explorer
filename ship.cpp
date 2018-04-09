#include "ship.h"
#include "ui_ship.h"
#include "mainwindow.h"

#include <QDebug>
#include <QAbstractButton>
#include <QPicture>
#include <QPainter>
#include <QRect>
#include <QPainterPath>
#include <QCheckBox>
#include <cmath>

//typedef std::vector<QLabel>::iterator symbolsIt;

//CONSTANT
const int ship::MAX_JOURNEYS = 40;
const mappedCheckboxRef ship::CHECKBOX_REF = {{"cb0",0},{"cb1",1},{"cb2",2},
                                            {"cb3",3},{"cb4",4},{"cb5",5},
                                             {"cb6",6},{"cb7",7},{"cb8",8}};
//PRIVATE + STATIC
int ship::cbCounter = 0;

ship::ship(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ship)
{
    ui->setupUi(this);

    cbRecord.reserve(5);
    symbolBits = QBitArray(9);

    symbolImgs.reserve(MAX_JOURNEYS); //TODO: add this limit elsewhere.
    for (int i = 0; i < MAX_JOURNEYS; i++){
        QLabel *test = new QLabel(this);
        test->setPixmap(QPixmap(":/resources/symbol.png"));
        symbolImgs.push_back(test);
    }

    ui->shipProgressBar->setValue(40);

    connect(ui->cbGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(handleCheckedBox(QAbstractButton*)));
    connect(ui->launchButton, SIGNAL(released()),this, SIGNAL(launchButtonReleased()));
    //connect(ui->launchButton, SIGNAL(released()), this, SLOT(MainWindow::handleLaunchClick()));
}

ship::~ship() {
    delete ui;
}

//add qlabel of the symbol (of the island you just went to) to the top of the screen.
void ship::addSymbolLabel(){
    QLabel *symb = symbolImgs[MAX_JOURNEYS - MainWindow::symbolCounter];
    QString symbolNum = QString::number(MAX_JOURNEYS - MainWindow::symbolCounter);
    QString imgPath = "//Users//mavis//QTprojects//dot//symbolStorage//symbol" + symbolNum + ".png";
    QImage img = QImage(imgPath).scaled(QSize(28,28));
    symb->move(QPoint(18 * (MAX_JOURNEYS - MainWindow::symbolCounter),0));
    symb->setPixmap(QPixmap::fromImage(img));
}

void ship::setProgressValue(int val){
    if (val <= 40 && val > -1){
        ui->shipProgressBar->setValue(val);
    } else {
        qDebug("Error: Can't set the progress bar to that value.");
    }
}


void ship::handleCheckedBox(QAbstractButton * cb){
    //--- note: 'cb' = 'CheckButton' ---//
    QObject *o = cb;
    QString cbName = o->objectName();
    int cbID = 0; //initialization only

    mappedCheckboxRef::const_iterator iter = CHECKBOX_REF.find(cbName);
    if (iter == CHECKBOX_REF.end()){
        qDebug("Error in finding the checkbox selected!");
    } else {
        cbID = iter->second;
    }
    //----------------------------------------------------//
    /* IF: The user hasn't checked [5] boxes yet. */
    if (cbCounter < 5){
        if (cb->isChecked()){
            //User checked a box. Record this.
            cbCounter++;
            if (cbID >= 0 && cbID < 9){ cbRecord.push_back(cbID); }
            if (cbCounter == 5) { _makeSymbol(); }
            //done :)
        } else {
            //User unchecked a box. Remove that from record.
            if (cbCounter > 0) {
                cbCounter--;
                std::vector<int>::iterator pos = std::find(cbRecord.begin(), cbRecord.end(), cbID);
                if (pos != cbRecord.end()) { cbRecord.erase(pos); }
            }
        }
    /* ELSE: The user has gone over the checked limit of [5] */
    } else {
        if (cb->isChecked()){
            //User went over the limit
            //(dealt with by stubbornly unchecking the box that was just checked)
            cb->setChecked(false);
        } else {
            //User unchecked a box. Remove that from record.
            if (cbCounter > 0) {
                cbCounter--;
                std::vector<int>::iterator pos = std::find(cbRecord.begin(), cbRecord.end(), cbID);
                if (pos != cbRecord.end()) { cbRecord.erase(pos); }
            }
        }
    }
}

//used by handleCheckedBox
//TODO: send in which checkboxes were pressed.
/*OPTIONS (note: the width is 3)
 * 0 1 2
 * 3 4 5
 * 6 7 8
 /*--------------------------------*/
void ship::_makeSymbol(){
    //QPicture pic;
    QImage pic(":/resources/symbol.png");
    QPainter painter(&pic);

    int q = (ui->paintContainer->width())/4; //'a quarter'. note: width should equal height

    QPen linePen((QColor::QColor(0,0,0)),5);
    linePen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(linePen);

    QPainterPath path;

    QPoint firstPoint = getXYFromIndex(cbRecord[0],q);
    path.moveTo(firstPoint);
    for (int i = 1; i < cbRecord.size(); i++){
        QPoint temp = getXYFromIndex(cbRecord[i],q);
        path.lineTo(temp);
    }

    painter.drawPath(path);
    painter.end();
    ui->paintContainer->setPixmap(QPixmap::fromImage(pic));
    QString imgPath = "//Users//mavis//QTprojects//dot//symbolStorage//temp_symbol.png";
    if (pic.save(imgPath)){
        qDebug("Symbol saved successfully.");
    } else {
        qDebug("Problem saving symbol.");
    }
}

//specific to the makeSymbol function ( ie the +1 ). Seperation is the space between points.
//could make it not specific...?
QPoint ship::getXYFromIndex(int index, int seperation){
    int x = ((index%3)+1)*seperation;
    int y = ((index/3)+1)*seperation;
    QString msg = QString::number(x);
    QString msg2 = QString::number(y);
    return QPoint(x, y);
}

/* -----GETTERS and SETTERS----- */

std::vector<int> ship::getCBRecord(){
    return cbRecord;
}
QBitArray ship::getSymbolBits(){
    return symbolBits;
}
int ship::getCurrentSymbolID(){
    return currentSymbolID;
}
void ship::setCurrentSymbolID(int id){
    currentSymbolID = id;
}
