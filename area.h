#ifndef AREA_H
#define AREA_H

#include "lookwindow.h"
#include "inv.h"

#include <QWidget>
#include <QAbstractButton>
#include <QString>
#include <vector>
#include <array>

namespace Ui {
class area;
}

class area : public QWidget
{
    Q_OBJECT

public:
    static const std::array<QString, 20> outsideImages;
    explicit area(QWidget *parent = 0);
    void setOutsideImage(int,int);
    void setSectionMarker(int);

    ~area();

private:
    Ui::area *ui;
    std::vector<QString> takenItemsTemp;

private slots:
    void handleLookButton();

signals:
    void lookDialogClosed();
    void sectionButtonReleased(QAbstractButton*);
};

#endif // AREA_H
