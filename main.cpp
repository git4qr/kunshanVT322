#include "dialog.h"
#include <QApplication>
#include "programmer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Programmer p;
    Dialog d;
    d.show();

    a.connect(&d,SIGNAL(toProgrammer()),&p,SLOT(receiceProgrammer()));//dialog跳转到Programmer

    a.connect(&p,SIGNAL(toPlatformConfig()),&d,SLOT(receivePlatConfig()));
    a.connect(&p,SIGNAL(toPID()),&d,SLOT(receivePID()));
    a.connect(&p,SIGNAL(toJosHandle()),&d,SLOT(receiveJoshandle()));
    a.connect(&p,SIGNAL(toJosMap1()),&d,SLOT(receiveJosMap1()));
    a.connect(&p,SIGNAL(toJosMap2()),&d,SLOT(receiceJosMap2()));
    a.connect(&p,SIGNAL(toKeyboardmap1()),&d,SLOT(receiceKeyboardMap1()));
    a.connect(&p,SIGNAL(toKeyboardmap2()),&d,SLOT(receiveKeyboardMap2()));
    a.connect(&p,SIGNAL(toUTC1()),&d,SLOT(receiveUTC1()));
    a.connect(&p,SIGNAL(toUTC2()),&d,SLOT(receiveUTC2()));
    a.connect(&p,SIGNAL(toUTC3()),&d,SLOT(receiveUTC3()));
    a.connect(&p,SIGNAL(toSerial()),&d,SLOT(receiveSerial()));
    a.connect(&p,SIGNAL(toEM()),&d,SLOT(receiveEM()));
    a.connect(&p,SIGNAL(toOSD1()),&d,SLOT(receiveOSD1()));
    a.connect(&p,SIGNAL(toOSD2()),&d,SLOT(receiveOSD2()));
    a.connect(&p,SIGNAL(toOSD3()),&d,SLOT(receiveOSD3()));
    a.connect(&p,SIGNAL(toCamera1()),&d,SLOT(receiveCamera1()));
    a.connect(&p,SIGNAL(toCamera2()),&d,SLOT(receiveCamera2()));
    a.connect(&p,SIGNAL(toCamera3()),&d,SLOT(receiveCamera3()));
    a.connect(&p,SIGNAL(toCamera4()),&d,SLOT(receiveCamera4()));
    a.connect(&p,SIGNAL(toCamera5()),&d,SLOT(receiveCamera5()));
    a.connect(&p,SIGNAL(toCamera6()),&d,SLOT(receiveCamera6()));
    a.connect(&p,SIGNAL(toCamera7()),&d,SLOT(receiveCamera7()));
    a.connect(&p,SIGNAL(toCamera8()),&d,SLOT(receiveCamera8()));
    a.connect(&p,SIGNAL(toCamera9()),&d,SLOT(receiveCamera9()));
    a.connect(&p,SIGNAL(toCamera10()),&d,SLOT(receiveCamera10()));
    a.connect(&p,SIGNAL(toCamera11()),&d,SLOT(receiveCamera11()));
    a.connect(&p,SIGNAL(toCamera12()),&d,SLOT(receiveCamera12()));
    a.connect(&p,SIGNAL(toCamera13()),&d,SLOT(receiveCamera13()));
    a.connect(&p,SIGNAL(toCamera14()),&d,SLOT(receiveCamera14()));
    a.connect(&p,SIGNAL(toCamera15()),&d,SLOT(receiveCamera15()));
    a.connect(&p,SIGNAL(toCamera16()),&d,SLOT(receiveCamera15()));
    a.connect(&p,SIGNAL(toCamera17()),&d,SLOT(receiveCamera17()));
    a.connect(&p,SIGNAL(toCamera18()),&d,SLOT(receiveCamera18()));
    a.connect(&p,SIGNAL(toCamera19()),&d,SLOT(receiveCamera19()));
    a.connect(&p,SIGNAL(toCamera20()),&d,SLOT(receiveCamera20()));
    a.connect(&p,SIGNAL(toCamera21()),&d,SLOT(receiveCamera21()));
    a.connect(&p,SIGNAL(toCamera22()),&d,SLOT(receiveCamera22()));
    a.connect(&p,SIGNAL(toCamera23()),&d,SLOT(receiveCamera23()));
    a.connect(&p,SIGNAL(toCamera24()),&d,SLOT(receiveCamera24()));
    a.connect(&p,SIGNAL(toCamera25()),&d,SLOT(receiveCamera25()));
    a.connect(&p,SIGNAL(toCamera26()),&d,SLOT(receiveCamera26()));
    a.connect(&p,SIGNAL(toCamera27()),&d,SLOT(receiveCamera27()));
    return a.exec();
}
