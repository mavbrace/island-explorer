#include "mainwindow.h"
#include "areamanager.h"
#include <QApplication>
#include <QDebug>
#include <random>

#include "Dot.h"

/* Mavis Brace, 17058368 */
/* CS4076, Spring 2018 */
/* To implement: Buttons, check-boxes, [combo-boxes], icons, menus, [radio buttons], scrollbars,
 * [sliders], status bars, [text boxes], [toolbars] and [tooltips] */
/* Classes, objects, destructors, pre-processor directives, function prototypes & coercion, pointers,
 * references, inheritance, memory mangagement, templates, operator overloading,
 * abstract classes, pure virtual functions */

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(0)); //seed the random generator.
    Dot d;

    MainWindow w;
    w.setStyleSheet("QMainWindow { background: #EEF7F3; }");
    w.show();

    return a.exec();
}

Dot::Dot() {
    //new game.........
}


