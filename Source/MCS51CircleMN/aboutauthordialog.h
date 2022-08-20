#ifndef ABOUTAUTHORDIALOG_H
#define ABOUTAUTHORDIALOG_H

#include <QWidget>

namespace Ui {
class AboutAuthorDialog;
}

class AboutAuthorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AboutAuthorDialog(QWidget *parent = nullptr);
    ~AboutAuthorDialog();

private:
    Ui::AboutAuthorDialog *ui;
};

#endif // ABOUTAUTHORDIALOG_H
