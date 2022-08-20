#ifndef UARTCANCELDIALOG_H
#define UARTCANCELDIALOG_H

#include <QWidget>

namespace Ui {
class uartcanceldialog;
}

class uartcanceldialog : public QWidget
{
    Q_OBJECT

public:
    explicit uartcanceldialog(QWidget *parent = nullptr);
    ~uartcanceldialog();

private:
    Ui::uartcanceldialog *ui;
};

#endif // UARTCANCELDIALOG_H
