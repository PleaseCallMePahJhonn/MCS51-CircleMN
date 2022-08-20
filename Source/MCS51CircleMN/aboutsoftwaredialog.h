#ifndef ABOUTSOFTWAREDIALOG_H
#define ABOUTSOFTWAREDIALOG_H

#include <QWidget>

namespace Ui {
class AboutSoftwareDialog;
}

class AboutSoftwareDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AboutSoftwareDialog(QWidget *parent = nullptr);
    ~AboutSoftwareDialog();

private:
    Ui::AboutSoftwareDialog *ui;
};

#endif // ABOUTSOFTWAREDIALOG_H
