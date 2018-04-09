#ifndef SHIP_H
#define SHIP_H

#include <QWidget>
#include <QAbstractButton>
#include <QPoint>
#include <QString>
#include <QLabel>

#include <vector>
#include <QBitArray>

typedef std::map<QString, int> mappedCheckboxRef;

namespace Ui {
class ship;
}

class ship : public QWidget
{
    Q_OBJECT

public:
    static const int MAX_JOURNEYS;
    static const mappedCheckboxRef CHECKBOX_REF;
    explicit ship(QWidget *parent = 0);
    void _makeSymbol();
    QPoint getXYFromIndex(int, int);
    void addSymbolLabel();
    //--getters and setters--//
    std::vector<int> getCBRecord();
    QBitArray getSymbolBits();
    int getCurrentSymbolID();
    void setCurrentSymbolID(int);
    void setProgressValue(int);
    ~ship();

public slots:
    void handleCheckedBox(QAbstractButton * cb);

signals:
    void launchButtonReleased();

private:
    Ui::ship *ui;
    static int cbCounter;
    std::vector<int> cbRecord; //cb ids
    std::vector<QLabel*> symbolImgs;
    QBitArray symbolBits; // 0 or 1
    int currentSymbolID; //symbolBits to int = symbolId. !!!
};

#endif // SHIP_H
