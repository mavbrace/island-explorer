#include <QKeyEvent>
#include "keypress.h"

KeyPress::KeyPress( QWidget *parent) : QWidget(parent ) {
    qDebug("HELLO?");
}

void KeyPress::keyReleaseEvent(QKeyEvent *event){
    qDebug("Released!");
    if(event->key() == Qt::Key_Up){
        qDebug("UP");
    }else if(event->key() == Qt::Key_Down){
        qDebug("DOWN");
    }
}

