#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString fileDirectory;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_pushButton_6_clicked();

    void on_checkBox_uart_en_toggled(bool checked);

    void on_checkBox_t1_en_toggled(bool checked);

    void on_checkBox_t0_en_toggled(bool checked);

    void on_checkBox_t0it_2_toggled(bool checked);

    void on_checkBox_t0_pulse_en_toggled(bool checked);

    void on_comboBox_t0mode_pulse_currentIndexChanged(int index);

    void on_lineEdit_t0_pulse_editingFinished();

    void on_checkBox_t1it_2_toggled(bool checked);

    void on_checkBox_t1_pulse_en_toggled(bool checked);

    void on_lineEdit_t1_pulse_editingFinished();

    void on_comboBox_t1mode_pulse_currentIndexChanged(int index);

    void on_pushButton_calculate_clicked();

    void on_comboBox_cal_mode_currentIndexChanged(int index);

    void on_pushButton_fromt0_clicked();

    void on_pushButton_fromt1_clicked();

    void on_lineEdit_xtal_editingFinished();

    void on_comboBox_txmode_toreg_currentIndexChanged(int index);

    void on_pushButton_tot0_clicked();

    void on_pushButton_tot1_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Widget *ui;
    void ChangeProjectName(QString fileName_proj);
    void ConfigureT0();
    void ConfigureT1();
    void TimInclude();
    void TimHeader();
    void UartInclude();
    void ConfigUart();
    void UartHeader();
    void ExtiInclude();
    void ConfigureExti0();
    void ConfigureExti1();
    void ExtiHeader();
    void ConfigureMain();
    void PulseToRegT0();
    void PulseToRegT1();
    void GenerateAll();
};
#endif // WIDGET_H
