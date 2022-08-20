#ifndef T1CANCELDIALOG_H
#define T1CANCELDIALOG_H

#include <QWidget>

namespace Ui {
class t1CancelDialog;
}

class t1CancelDialog : public QWidget
{
    Q_OBJECT

public:
    explicit t1CancelDialog(QWidget *parent = nullptr);
    ~t1CancelDialog();

private:
    Ui::t1CancelDialog *ui;
};

#endif // T1CANCELDIALOG_H
