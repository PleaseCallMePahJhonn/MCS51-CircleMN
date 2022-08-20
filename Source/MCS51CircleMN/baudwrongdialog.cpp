#include "baudwrongdialog.h"
#include "ui_baudwrongdialog.h"

BaudWrongDialog::BaudWrongDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaudWrongDialog)
{
    ui->setupUi(this);
}

BaudWrongDialog::~BaudWrongDialog()
{
    delete ui;
}
