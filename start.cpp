#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

    connect(ui->goButton, SIGNAL(released()), this, SLOT (close()));
}

Start::~Start()
{
    delete ui;
}

