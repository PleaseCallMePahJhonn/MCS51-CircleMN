#include "t1canceldialog.h"
#include "ui_t1canceldialog.h"

t1CancelDialog::t1CancelDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::t1CancelDialog)
{
    ui->setupUi(this);
}

t1CancelDialog::~t1CancelDialog()
{
    delete ui;
}
