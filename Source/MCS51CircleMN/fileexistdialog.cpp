#include "fileexistdialog.h"
#include "ui_fileexistdialog.h"
#include "widget.h"
#include <QDebug>

fileExistDialog::fileExistDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileExistDialog)
{
    ui->setupUi(this);
}

fileExistDialog::~fileExistDialog()
{
    delete ui;
}



void fileExistDialog::on_pushButton_clicked()
{
    //
}
