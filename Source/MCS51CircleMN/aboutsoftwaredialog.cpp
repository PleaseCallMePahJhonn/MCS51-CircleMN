#include "aboutsoftwaredialog.h"
#include "ui_aboutsoftwaredialog.h"

AboutSoftwareDialog::AboutSoftwareDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutSoftwareDialog)
{
    ui->setupUi(this);
}

AboutSoftwareDialog::~AboutSoftwareDialog()
{
    delete ui;
}
