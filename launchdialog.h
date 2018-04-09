#ifndef LAUNCHDIALOG_H
#define LAUNCHDIALOG_H

#include <QDialog>

namespace Ui {
class launchDialog;
}

class launchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit launchDialog(QWidget *parent = 0);
    ~launchDialog();
    void setDesc1(QString);
    void setDesc2(QString);

private:
    Ui::launchDialog *ui;
};

#endif // LAUNCHDIALOG_H
