#include "programmer.h"
#include "ui_programmer.h"
#include "dialog.h"
Programmer::Programmer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Programmer)
{
    ui->setupUi(this);
    this->setWindowTitle("程序员配置");
}

Programmer::~Programmer()
{
    delete ui;
}


void Programmer::on_btnPlatformConfig_clicked()
{
    this->showMinimized();
    emit toPlatformConfig();

}

void Programmer::on_btnPID_clicked()
{
    this->showMinimized();
    emit toPID();
}

void Programmer::on_btnJosHdl_clicked()
{
    this->showMinimized();
    emit toJosHandle();
}

void Programmer::on_btnJosMap1_clicked()
{
    this->showMinimized();
    emit toJosMap1();
}

void Programmer::on_btnJosMap2_clicked()
{
    this->showMinimized();
    emit toJosMap2();
}

void Programmer::on_btnKeyboardMap1_clicked()
{
    this->showMinimized();
    emit toKeyboardmap1();
}

void Programmer::on_btnKeyboardMap2_clicked()
{
    this->showMinimized();
    emit toKeyboardmap2();
}

void Programmer::on_btnUTC1_clicked()
{
    this->showMinimized();
    emit toUTC1();
}

void Programmer::on_btnUTC2_clicked()
{
    this->showMinimized();
    emit toUTC2();
}

void Programmer::on_btnUTC3_clicked()
{
    this->showMinimized();
    emit toUTC3();
}

void Programmer::on_btnSerialParam_clicked()
{
    this->showMinimized();
    emit toSerial();
}

void Programmer::on_btnEnhMmt_clicked()
{
    this->showMinimized();
    emit toEM();
}

void Programmer::on_btnOSD1_clicked()
{
    this->showMinimized();
    emit toOSD1();
}

void Programmer::on_btnOSD2_clicked()
{
    this->showMinimized();
    emit toOSD2();
}

void Programmer::on_btnOSD3_clicked()
{
    this->showMinimized();
    emit toOSD3();
}

void Programmer::on_btnCamera1_clicked()
{
    this->showMinimized();
    emit toCamera1();
}

void Programmer::on_btnCamera2_clicked()
{
    this->showMinimized();
    emit toCamera2();
}

void Programmer::on_btnCamera4_clicked()
{
    this->showMinimized();
    emit toCamera4();
}



void Programmer::on_btnCamera3_clicked()
{
    this->showMinimized();
    emit toCamera3();
}

void Programmer::on_btnCamera5_clicked()
{
    this->showMinimized();
    emit toCamera5();
}

void Programmer::on_btnCamera6_clicked()
{
    this->showMinimized();
    emit toCamera6();
}

void Programmer::on_btnCamera7_clicked()
{
    this->showMinimized();
    emit toCamera7();
}

void Programmer::on_btnCamera8_clicked()
{
    this->showMinimized();
    emit toCamera8();
}

void Programmer::on_btnCamera9_clicked()
{
    this->showMinimized();
    emit toCamera9();
}

void Programmer::on_btnCamera10_clicked()
{
    this->showMinimized();
    emit toCamera10();
}

void Programmer::on_btnCamera11_clicked()
{
    this->showMinimized();
    emit toCamera11();
}

void Programmer::on_btnCamera12_clicked()
{
    this->showMinimized();
    emit toCamera12();
}

void Programmer::on_btnCamera13_clicked()
{
    this->showMinimized();
    emit toCamera13();
}

void Programmer::on_btnCamera14_clicked()
{
    this->showMinimized();
    emit toCamera14();
}

void Programmer::on_btnCamera15_clicked()
{
    this->showMinimized();
    emit toCamera15();
}

void Programmer::on_btnCamera16_clicked()
{
    this->showMinimized();
    emit toCamera16();
}

void Programmer::on_btnCamera17_clicked()
{
    this->showMinimized();
    emit toCamera17();
}

void Programmer::on_btnCamera18_clicked()
{
    this->showMinimized();
    emit toCamera18();
}

void Programmer::on_btnCamera19_clicked()
{
    this->showMinimized();
    emit toCamera19();
}

void Programmer::on_btnCamera20_clicked()
{
    this->showMinimized();
    emit toCamera20();
}

void Programmer::on_btnCamera21_clicked()
{
    this->showMinimized();
    emit toCamera21();
}

void Programmer::on_btnCamera22_clicked()
{
    this->showMinimized();
    emit toCamera22();
}

void Programmer::on_btnCamera23_clicked()
{
    this->showMinimized();
    emit toCamera23();
}

void Programmer::on_btnCamera24_clicked()
{
    this->showMinimized();
    emit toCamera24();
}

void Programmer::on_btnCamera25_clicked()
{
    this->showMinimized();
    emit toCamera25();
}

void Programmer::on_btnCamera26_clicked()
{
    this->showMinimized();
    emit toCamera26();
}

void Programmer::on_btnCamera27_clicked()
{
    this->showMinimized();
    emit toCamera27();
}

void Programmer::receiceProgrammer()
{
    this->show();
}
