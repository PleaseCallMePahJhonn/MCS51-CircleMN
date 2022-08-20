#ifndef TIMECOPIEDDIALOG_H
#define TIMECOPIEDDIALOG_H

#include <QWidget>

namespace Ui {
class TimeCopiedDialog;
}

class TimeCopiedDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TimeCopiedDialog(QWidget *parent = nullptr);
    ~TimeCopiedDialog();

private:
    Ui::TimeCopiedDialog *ui;
};

#endif // TIMECOPIEDDIALOG_H
