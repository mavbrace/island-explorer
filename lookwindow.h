#ifndef LOOKWINDOW_H
#define LOOKWINDOW_H

#include <QDialog>
#include <QString>
#include <vector>

namespace Ui {
class lookWindow;
}

class lookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit lookWindow(QWidget *parent = 0);
    static QString descOfItems;
    static std::vector<QString> itemNames;
    static std::vector<QString> takenItemNames;
    ~lookWindow();

private:
    Ui::lookWindow *ui;

public slots:
    void handleTakeButton();
};

#endif // LOOKWINDOW_H
