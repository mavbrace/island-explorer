#ifndef INV_H
#define INV_H

#include "item.h"
#include <QWidget>
#include <QString>
#include <vector>

namespace Ui {
class inv;
}

class inv : public QWidget
{
    Q_OBJECT

public:
    explicit inv(QWidget *parent = 0);
    void addItemObjects(std::vector<item*>);
    void removeFromItemObjects(QString);
    void removeItemFully(int);
    int getItemIndexFromName(QString);
    ~inv();

private:
    Ui::inv *ui;
    std::vector<item*> itemObjects;
    QString warningDefaultMsg;

public slots:
    void handleLookWindowClosed();
    void handleTossButton();
    void handleEatButton();
    void handleBurnButton();
};

#endif // INV_H
