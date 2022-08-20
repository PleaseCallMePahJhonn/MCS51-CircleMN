#include "timewrongdialog.h"
#include "ui_timewrongdialog.h"

timeWrongDialog::timeWrongDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timeWrongDialog)
{
    ui->setupUi(this);
}

timeWrongDialog::~timeWrongDialog()
{
    delete ui;
}
