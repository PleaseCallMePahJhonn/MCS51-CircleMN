#ifndef TIMWRONGDIALOG_H
#define TIMWRONGDIALOG_H

#include <QWidget>

namespace Ui {
class TimWrongDialog;
}

class TimWrongDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TimWrongDialog(QWidget *parent = nullptr);
    ~TimWrongDialog();

private:
    Ui::TimWrongDialog *ui;
};

#endif // TIMWRONGDIALOG_H
