#ifndef COPYSUCCESSFULDIALOG_H
#define COPYSUCCESSFULDIALOG_H

#include <QWidget>

namespace Ui {
class CopySuccessfulDialog;
}

class CopySuccessfulDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CopySuccessfulDialog(QWidget *parent = nullptr);
    ~CopySuccessfulDialog();

private:
    Ui::CopySuccessfulDialog *ui;
};

#endif // COPYSUCCESSFULDIALOG_H
