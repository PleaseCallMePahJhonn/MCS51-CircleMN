#ifndef GENFINISHDIALOG_H
#define GENFINISHDIALOG_H

#include <QWidget>

namespace Ui {
class GenFinishDialog;
}

class GenFinishDialog : public QWidget
{
    Q_OBJECT

public:
    explicit GenFinishDialog(QWidget *parent = nullptr);
    ~GenFinishDialog();

private:
    Ui::GenFinishDialog *ui;
};

#endif // GENFINISHDIALOG_H
