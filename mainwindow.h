#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ship.h"
#include "areamanager.h"

#include <QMainWindow>
#include <QPushButton>
#include <vector>

typedef std::vector<areaManager*>::iterator islandsVecIt;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    static int symbolCounter;
    int findTabIndex(int incr);
    bool prepDestInfo();

private slots:
public slots:
    void handleLaunchClick();
    void handleSectionButton(QAbstractButton * button);
    void handleLookWindowClosed();
    void switchToPortholeTab();
    void handleEndGameButton();
    void quitGame();

protected:
    void keyReleaseEvent(QKeyEvent*);

private:
    QTabWidget *tabs;
    QPushButton *endGameButton;

    QWidget *porthole;
    QWidget *shipControl;
    QWidget *invWidget;

    ship *testship;
    area *areaPorthole;
    inv *inventory;

    std::vector<areaManager*> islands; //cb ids
    areaManager **onThisIsland;
};

#endif // MAINWINDOW_H
