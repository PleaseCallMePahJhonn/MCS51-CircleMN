#include "genfinishdialog.h"
#include "ui_genfinishdialog.h"

GenFinishDialog::GenFinishDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenFinishDialog)
{
    ui->setupUi(this);
}

GenFinishDialog::~GenFinishDialog()
{
    delete ui;
}
