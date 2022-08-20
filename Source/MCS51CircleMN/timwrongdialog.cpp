#include "timwrongdialog.h"
#include "ui_timwrongdialog.h"

TimWrongDialog::TimWrongDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimWrongDialog)
{
    ui->setupUi(this);
}

TimWrongDialog::~TimWrongDialog()
{
    delete ui;
}
