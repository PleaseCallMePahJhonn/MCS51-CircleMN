#ifndef TIMEWRONGDIALOG_H
#define TIMEWRONGDIALOG_H

#include <QWidget>

namespace Ui {
class timeWrongDialog;
}

class timeWrongDialog : public QWidget
{
    Q_OBJECT

public:
    explicit timeWrongDialog(QWidget *parent = nullptr);
    ~timeWrongDialog();

private:
    Ui::timeWrongDialog *ui;
};

#endif // TIMEWRONGDIALOG_H
