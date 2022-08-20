#include "uartcanceldialog.h"
#include "ui_uartcanceldialog.h"

uartcanceldialog::uartcanceldialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uartcanceldialog)
{
    ui->setupUi(this);
}

uartcanceldialog::~uartcanceldialog()
{
    delete ui;
}
