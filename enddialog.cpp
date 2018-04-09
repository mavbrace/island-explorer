#include "enddialog.h"
#include "ui_enddialog.h"

endDialog::endDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endDialog)
{
    ui->setupUi(this);

    connect(ui->quitButton, SIGNAL(released()), qApp, SLOT(quit()));
}

endDialog::~endDialog()
{
    delete ui;
}
