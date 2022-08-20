#include "copysuccessfuldialog.h"
#include "ui_copysuccessfuldialog.h"

CopySuccessfulDialog::CopySuccessfulDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopySuccessfulDialog)
{
    ui->setupUi(this);
}

CopySuccessfulDialog::~CopySuccessfulDialog()
{
    delete ui;
}
