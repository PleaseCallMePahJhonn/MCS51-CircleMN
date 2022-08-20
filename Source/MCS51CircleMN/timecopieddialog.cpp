#include "timecopieddialog.h"
#include "ui_timecopieddialog.h"

TimeCopiedDialog::TimeCopiedDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeCopiedDialog)
{
    ui->setupUi(this);
}

TimeCopiedDialog::~TimeCopiedDialog()
{
    delete ui;
}
