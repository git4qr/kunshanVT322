#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QWidget>

namespace Ui {
class Programmer;
}

class Programmer : public QWidget
{
    Q_OBJECT

public:
    explicit Programmer(QWidget *parent = 0);
    ~Programmer();

signals:
    /*******************用于跳转到配置界面的信号******************/
    void toPlatformConfig();//平台参数信号
    void toPID();//PID配置信号
    void toJosHandle();//Joshandle信号
    void toJosMap1();
    void toJosMap2();
    void toKeyboardmap1();
    void toKeyboardmap2();
    void toUTC1();
    void toUTC2();
    void toUTC3();
    void toSerial();
    void toEM();
    void toOSD1();
    void toOSD2();
    void toOSD3();
    void toCamera1();
    void toCamera2();
    void toCamera3();
    void toCamera4();
    void toCamera5();
    void toCamera6();
    void toCamera7();
    void toCamera8();
    void toCamera9();
    void toCamera10();
    void toCamera11();
    void toCamera12();
    void toCamera13();
    void toCamera14();
    void toCamera15();
    void toCamera16();
    void toCamera17();
    void toCamera18();
    void toCamera19();
    void toCamera20();
    void toCamera21();
    void toCamera22();
    void toCamera23();
    void toCamera24();
    void toCamera25();
    void toCamera26();
    void toCamera27();

private slots:
    void on_btnPlatformConfig_clicked();

    void on_btnPID_clicked();

    void on_btnJosHdl_clicked();

    void on_btnJosMap1_clicked();

    void on_btnJosMap2_clicked();

    void on_btnKeyboardMap1_clicked();

    void on_btnKeyboardMap2_clicked();

    void on_btnUTC1_clicked();

    void on_btnUTC2_clicked();

    void on_btnUTC3_clicked();

    void on_btnSerialParam_clicked();

    void on_btnEnhMmt_clicked();

    void on_btnOSD1_clicked();

    void on_btnOSD2_clicked();

    void on_btnOSD3_clicked();

    void on_btnCamera1_clicked();

    void on_btnCamera2_clicked();

    void on_btnCamera4_clicked();

    void on_btnCamera3_clicked();

    void on_btnCamera5_clicked();

    void on_btnCamera6_clicked();

    void on_btnCamera7_clicked();

    void on_btnCamera8_clicked();

    void on_btnCamera9_clicked();

    void on_btnCamera10_clicked();

    void on_btnCamera11_clicked();

    void on_btnCamera12_clicked();

    void on_btnCamera13_clicked();

    void on_btnCamera14_clicked();

    void on_btnCamera15_clicked();

    void on_btnCamera16_clicked();

    void on_btnCamera17_clicked();

    void on_btnCamera18_clicked();

    void on_btnCamera19_clicked();

    void on_btnCamera20_clicked();

    void on_btnCamera21_clicked();

    void on_btnCamera22_clicked();

    void on_btnCamera23_clicked();

    void on_btnCamera24_clicked();

    void on_btnCamera25_clicked();

    void on_btnCamera26_clicked();

    void on_btnCamera27_clicked();

    void receiceProgrammer();//接收来自dialog的信号

private:
    Ui::Programmer *ui;
};

#endif // PROGRAMMER_H
