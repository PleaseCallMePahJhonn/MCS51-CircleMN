#include "aboutauthordialog.h"
#include "ui_aboutauthordialog.h"

AboutAuthorDialog::AboutAuthorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutAuthorDialog)
{
    ui->setupUi(this);
}

AboutAuthorDialog::~AboutAuthorDialog()
{
    delete ui;
}
