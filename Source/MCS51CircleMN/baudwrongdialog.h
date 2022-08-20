#ifndef BAUDWRONGDIALOG_H
#define BAUDWRONGDIALOG_H

#include <QWidget>

namespace Ui {
class BaudWrongDialog;
}

class BaudWrongDialog : public QWidget
{
    Q_OBJECT

public:
    explicit BaudWrongDialog(QWidget *parent = nullptr);
    ~BaudWrongDialog();

private:
    Ui::BaudWrongDialog *ui;
};

#endif // BAUDWRONGDIALOG_H
