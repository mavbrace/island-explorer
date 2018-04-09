#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QWidget>

class KeyPress : public QWidget
{
    Q_OBJECT
public:
    KeyPress( QWidget *parent = 0);

protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // KEYEVENTRECEIVER_H
