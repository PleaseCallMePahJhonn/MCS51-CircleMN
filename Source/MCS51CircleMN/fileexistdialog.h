#ifndef FILEEXISTDIALOG_H
#define FILEEXISTDIALOG_H

#include <QWidget>

namespace Ui {
class fileExistDialog;
}

class fileExistDialog : public QWidget
{
    Q_OBJECT

public:
    explicit fileExistDialog(QWidget *parent = nullptr);
    ~fileExistDialog();


private slots:
    void on_pushButton_clicked();

private:
    Ui::fileExistDialog *ui;
};

#endif // FILEEXISTDIALOG_H
