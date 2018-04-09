#include "launchdialog.h"
#include "ui_launchdialog.h"

launchDialog::launchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::launchDialog)
{
    ui->setupUi(this);

    connect(ui->okayButton, SIGNAL(released()), this, SLOT (close()));

}

launchDialog::~launchDialog()
{
    delete ui;
}

void launchDialog::setDesc1(QString desc1){
    ui->message1->setText(desc1);
}

void launchDialog::setDesc2(QString desc2){
    ui->message2->setText(desc2);
}
