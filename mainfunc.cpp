#include "dialog.h"
#include "QMouseEvent"
#include "qpainter.h"
//#include<QMutex>
#include <QDebug>
#include "ui_dialog.h"
#include <QMessageBox>
#include <Qtimer>
#include <QFormLayout>

//#define PI 3.14159269798

//int set_config_count = 0;
//int get_config_count = 0;

int mousePress = 0;
QMutex send_mutex;
unsigned char send_arr[64];
unsigned short sectrk_x = 0;
unsigned short sectrk_y = 0;
 unsigned char output_array[64];
 unsigned char output_array_6[64];
 unsigned char output_array_7[64];
 unsigned char output_array_8[64];
extern int connect_flag;
extern int current_povstat;

typedef struct resp
{
    unsigned char autocheck;
    unsigned char sensor;
    unsigned char sensor_bind;
    unsigned char trk;
    unsigned char mmt;
    unsigned char mmtselect;
    unsigned char enh;
    unsigned char posmove;
    unsigned char axismove;
    unsigned char zoom;
    unsigned char sectrk;
    unsigned char mtd;
    unsigned char pinp;
    unsigned char sensor_trans;
    unsigned char vframerate;
    unsigned char vquality;
    unsigned char osdcolor;
    unsigned char osdfont;
    unsigned char osdsize;
    unsigned char setconfig;
    unsigned char getconfig;
    unsigned char downconfig;
    unsigned char saveconfig;
    unsigned char joyskeyboard;

}resp_t;
resp_t respstat = {0};

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    //paint.drawRect(POINTX-WIDTH/2, POINTY-HEIGHT/2, WIDTH, HEIGHT);
    // 反走样
    paint.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    // 设置画刷颜色
    paint.setBrush(QColor(200, 255, 250));
    paint.drawRect(POINTX-WIDTH/RATIO/2, POINTY-HEIGHT/RATIO/2, WIDTH/RATIO, HEIGHT/RATIO);
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    paint.drawLine(QPointF(a-5, b), QPointF(a+5, b));
    paint.drawLine(QPointF(a, b-5), QPointF(a, b+5));
    //paint.drawPoint(a,b);
}
void Dialog::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"mousePressEvent";
    mousePress = 1;
    //if(event->pos()==QPoint(a,b))
    //if(event->pos().x()==a&&event->pos().y()==b)
    if((abs(event->pos().x()-a)<=10)&&((event->pos().y()-b)<=10))
        m_dragging = 1;
    else
        m_dragging = 0;
}

void Dialog::mouseReleaseEvent ( QMouseEvent * e )//鼠标松开事件响应
{
    //qDebug()<<"mouseReleaseEvent";
    mousePress = 0;
        //QString str="("+QString::number(e->x())+","+QString::number(e->y())+")";
         //statusBar()->showMessage (tr("Mouser Released:")+str,3000);
}
void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"mouseMoveEvent,m_dragging="<<m_dragging;
    if (mousePress&&m_dragging)
    {
        if((abs(event->pos().x()-POINTX)<(WIDTH/RATIO/2))&&(abs(event->pos().y()-POINTY)<(HEIGHT/RATIO/2)))
        {
            sectrk_x = (event->pos().x()-POINTX)*RATIO+WIDTH/2;
            sectrk_y = (event->pos().y()-POINTY)*RATIO+HEIGHT/2;
             ui->label_xy->setText(tr("(")+QString::number(sectrk_x)+","+QString::number(sectrk_y)+")");
            a=event->pos().x();
            b=event->pos().y();
            if(0 == ui->comboBox_sectrk->currentIndex())
            {
                send_mutex.lock();
                send_arr[3] = 0x0b;
                send_arr[4] = 0x01;
                send_arr[5] = sectrk_x&0xff;
                send_arr[6] = (sectrk_x>>8)&0xff;
                send_arr[7] = sectrk_y&0xff;
                send_arr[8] = (sectrk_y>>8)&0xff;
                send_oneframe(10);
                send_mutex.unlock();
            }
            update();
            //repaint();
        }
    }
}

void Dialog::on_pushButton_send_clicked()
{
    bool checkf = true;
    QString sendData = ui->textEdit_ShowSndData->toPlainText();
    sndData_02 = string2hex(sendData,checkf);
    sendNum += sndData_02.length();

    if(checkf == true)
    {
        serialPort_command->write(sndData_02);
        ui->label_send_bytes->setNum(sendNum);
        ui->textEdit_ShowSndData->append(sendData);
    }
    sendData.clear();
}
void Dialog::send_oneframe(int length)
{
    send_arr[0] = 0xEB;
    send_arr[1] = 0x53;
    send_arr[2] = length;
    unsigned char sum=0;
    for(int n = 3; n<length-1; n++) {
        sum ^= send_arr[n];
     }
    send_arr[length-1] = sum;

    QString str1;
    for(int m = 0; m< length; m++){
        str1 += QString("%1").arg(send_arr[m]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
    }

    bool checkf = true;
    sndData_02 = string2hex(str1,checkf);
    sendNum += sndData_02.length();
    memset(&respstat, 0, sizeof(respstat));
    if(ui->checkBox_timeout->isChecked())
    {
        send_timer->start(timeval_select);
    }
    if(checkf == true){
        if(1 == connect_flag)
        {
            serialPort_command->write(sndData_02);
        }
        else if(2 == connect_flag)
        {
            socket->write(sndData_02);//通过网口发送数据
            socket->flush();
        }

    }

    ui->label_send_bytes->setNum(sendNum);
    ui->textEdit_ShowSndData->append(str1);
}

void Dialog::on_checkBox_autocheck_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        send_mutex.lock();
        send_arr[3] = 0x01;
        send_arr[4] = 0x01;
        send_oneframe(6);
        send_mutex.unlock();
    }
    else if(arg1 == Qt::Unchecked)
    {
        send_mutex.lock();
        send_arr[3] = 0x01;
        send_arr[4] = 0x02;
        send_oneframe(6);
        send_mutex.unlock();
    }
}

void Dialog::on_comboBox_channel_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 5:
            send_mutex.lock();
            send_arr[3] = 0x02;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_channelbind_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 5:
            send_mutex.lock();
            send_arr[3] = 0x03;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void Dialog::on_pushButton_trk_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x04;
    send_arr[4] = 0x00;
    send_oneframe(6);
    send_mutex.unlock();
}

void Dialog::on_comboBox_zoom_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x0a;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x0a;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x0a;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x0a;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_mmtselect_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x06;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x06;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x06;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x06;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 0x06;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_pushButton_mmt_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x05;
    send_arr[4] = 0x00;
    send_oneframe(6);
    send_mutex.unlock();
}
void Dialog::on_pushButton_mtd_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x0d;
    send_arr[4] = 0x00;
    send_oneframe(6);
    send_mutex.unlock();
}
void Dialog::on_pushButton_enh_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x07;
    send_arr[4] = 0x00;
    send_oneframe(6);
    send_mutex.unlock();
}
void Dialog::on_pushButton_pinp_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x0e;
    send_arr[4] = 0x00;
    send_arr[5] = ui->comboBox_subchannel->currentIndex();
    send_oneframe(7);
    send_mutex.unlock();
}
void Dialog::on_pushButton_up_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x00;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x00;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_down_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x00;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x00;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_left_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x01;
        send_arr[5] = 0x00;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x01;
        send_arr[5] = 0x00;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_right_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x02;
        send_arr[5] = 0x00;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x02;
        send_arr[5] = 0x00;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_lu_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x01;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x01;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_ld_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x01;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x01;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_ru_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x02;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x02;
        send_arr[5] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_rd_clicked()
{
    if(0 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x08;
        send_arr[4] = 0x02;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(1 == ui->comboBox_moveselect->currentIndex())
    {
        send_mutex.lock();
        send_arr[3] = 0x09;
        send_arr[4] = 0x02;
        send_arr[5] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
    }
}
void Dialog::on_pushButton_axissave_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x0c;
    send_oneframe(5);
    send_mutex.unlock();
}
void Dialog::on_comboBox_color_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 5:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x06;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 6:
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x07;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_font_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x21;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x21;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_fontsize_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x22;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x22;
            send_arr[4] = 0x06;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_osddisplay_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x24;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x24;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_optzoom_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x12;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x12;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x12;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_aperture_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x13;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x13;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x13;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_focal_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x14;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x14;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x14;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_videochannel_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 5:
            send_mutex.lock();
            send_arr[3] = 0x0f;
            send_arr[4] = 0x05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_frc_activated(int index)
{
    int framerate = ui->lineEdit_framerate->text().toInt();
    send_mutex.lock();
    send_arr[3] = 0x10;
    send_arr[4] = framerate;
    send_arr[5] = index;
    send_oneframe(7);
    send_mutex.unlock();
}
void Dialog::on_comboBox_videoq_activated(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x01;
            send_arr[5] = ui->comboBox_vqc->currentIndex();
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x02;
            send_arr[5] = ui->comboBox_vqc->currentIndex();
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x03;
            send_arr[5] = ui->comboBox_vqc->currentIndex();
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_vqc_activated(int index)
{
    switch (ui->comboBox_videoq->currentIndex())
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x01;
            send_arr[5] = index;
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x02;
            send_arr[5] = index;
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 0x11;
            send_arr[4] = 0x03;
            send_arr[5] = index;
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_keystatus_activated(int index)
{
    int keyvalue = ui->lineEdit_keyvalue->text().toInt();
    short keyx = ui->lineEdit_keyx->text().toShort();
    short keyy = ui->lineEdit_keyy->text().toShort();
    short keyz = ui->lineEdit_keyz->text().toShort();
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[3] = 0x32;
            send_arr[4] = 0x00;
            send_arr[5] = 0x00;
            send_arr[6] = 0x00;
            send_arr[6] = keyvalue;
            send_arr[6] |= (1<<7);
            send_arr[7] = (keyx&0xff);
            send_arr[8] = ((keyx>>8)&0xff);
            send_arr[9] = (keyy&0xff);;
            send_arr[10] = ((keyy>>8)&0xff);
            send_arr[11] = (keyz&0xff);
            send_arr[12] = ((keyz>>8)&0xff);
            send_arr[13] = (65535&0xff);
            send_arr[14] = ((65535>>8)&0xff);
            send_oneframe(16);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[3] = 0x32;
            send_arr[4] = 0x00;
            send_arr[5] = 0x00;
            send_arr[6] = 0x00;
            send_arr[6] = keyvalue;
            send_arr[6] &= ~(1<<7);
            send_arr[7] = (keyx&0xff);
            send_arr[8] = ((keyx>>8)&0xff);
            send_arr[9] = (keyy&0xff);;
            send_arr[10] = ((keyy>>8)&0xff);
            send_arr[11] = (keyz&0xff);
            send_arr[12] = ((keyz>>8)&0xff);
            send_arr[13] = (65535&0xff);
            send_arr[14] = ((65535>>8)&0xff);
            send_oneframe(16);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}
void Dialog::on_comboBox_sectrk_activated(int index)
{
    if(1 == index)
    {
        send_mutex.lock();
        send_arr[3] = 0x0b;
        send_arr[4] = 0x02;
        send_arr[5] = sectrk_x&0xff;
        send_arr[6] = (sectrk_x>>8)&0xff;
        send_arr[7] = sectrk_y&0xff;
        send_arr[8] = (sectrk_y>>8)&0xff;
        send_oneframe(10);
        send_mutex.unlock();
    }
}

void Dialog::init_table()
{
    ui->tableWidget->setRowCount(12);//设置表格行数
    ui->tableWidget->setColumnCount(4);//设置表格列数
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,110);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,210);

    ui->tableWidget->setItem(0,0, new QTableWidgetItem("启动自检"));
    ui->tableWidget->setItem(1,0, new QTableWidgetItem("ACK"));
    ui->tableWidget->setItem(2,0, new QTableWidgetItem("NAK"));
    ui->tableWidget->setItem(3,0, new QTableWidgetItem("主视频通道"));
    ui->tableWidget->setItem(4,0, new QTableWidgetItem("绑定通道"));
    ui->tableWidget->setItem(5,0, new QTableWidgetItem("跟踪状态"));
    ui->tableWidget->setItem(6,0, new QTableWidgetItem("跟踪类型"));
    ui->tableWidget->setItem(7,0, new QTableWidgetItem("跟踪偏差"));
    ui->tableWidget->setItem(8,0, new QTableWidgetItem("多目标提示"));
    ui->tableWidget->setItem(9,0, new QTableWidgetItem("多目标编号"));
    ui->tableWidget->setItem(10,0, new QTableWidgetItem("图像增强"));
    ui->tableWidget->setItem(11,0, new QTableWidgetItem("跟踪微调"));

    ui->tableWidget->setItem(0,2, new QTableWidgetItem("校轴"));
    ui->tableWidget->setItem(1,2, new QTableWidgetItem("电子变倍"));
    ui->tableWidget->setItem(2,2, new QTableWidgetItem("跟搜"));
    ui->tableWidget->setItem(3,2, new QTableWidgetItem("运动目标检测"));
    ui->tableWidget->setItem(4,2, new QTableWidgetItem("画中画"));
    ui->tableWidget->setItem(5,2, new QTableWidgetItem("视频传输通道"));
    ui->tableWidget->setItem(6,2, new QTableWidgetItem("视频帧频"));
    ui->tableWidget->setItem(7,2, new QTableWidgetItem("视频压缩质量"));
    ui->tableWidget->setItem(8,2, new QTableWidgetItem("设置命令响应"));
    ui->tableWidget->setItem(9,2, new QTableWidgetItem("读命令响应"));
    ui->tableWidget->setItem(10,2, new QTableWidgetItem("手柄键盘响应"));
    ui->tableWidget->setItem(11,2, new QTableWidgetItem("保存配置响应"));

    ui->tableWidget->setItem(0,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(3,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(5,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(7,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(9,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(10,1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(11,1, new QTableWidgetItem(""));

    ui->tableWidget->setItem(0,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(1,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(2,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(3,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(4,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(5,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(6,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(7,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(8,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(9,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(10,3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(11,3, new QTableWidgetItem(""));

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("项")<<tr("描述")<<tr("项")<<tr("描述"));//设置水平方向的表头
    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);//隐藏竖直方向的表头
}
void Dialog::init_table_Profile()
{

    tableWidget_Profile->setRowCount(16);
    tableWidget_Profile->setColumnCount(2);
    tableWidget_Profile->setColumnWidth(0,180);
    tableWidget_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    //QHeaderView* headerView = tableWidget_Profile->verticalHeader();
    //headerView->setHidden(true);//隐藏竖直方向的表头
    load_config_flag = 1;
    load_profile();
    load_config_flag = 0;
}
void Dialog::init_table_camera_Profile()
{
    tabWidget_CameraParam1_camera_Profile->setRowCount(432);
    tabWidget_CameraParam1_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam1_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam1_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    //QHeaderView* headerView = tableWidget_camera_Profile->verticalHeader();
    //headerView->setHidden(true);//隐藏竖直方向的表头
    load_config_flag = 1;
    load_camera_profile();
    load_config_flag = 0;
}
void Dialog::output_to_label(int i)//解析下位机的反馈信息,从串口读到正确的一帧数据的时候执行此函数。
{
    int flag = 0;
    float value1 = 0;
    float value2 = 0;
    short trkerrx = 0;
    short trkerry = 0;
    switch(i)
    {
        case 0x01:
            respstat.autocheck = 1;
            ui->tableWidget->item(0,1)->setText("");
            if(0x01 == output_array[1])
            {
                ui->tableWidget->item(0,1)->setText("正常");
            }
            else if(0x02 == output_array[1])
            {
                ui->tableWidget->item(0,1)->setText("通道");
                if(output_array[2]&0x1 == 1)
                {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("0"));
                        flag = 1;
                }
                if((output_array[2]>>1)&0x1 == 1)
                {
                    if(flag)
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("/1"));
                    else
                    {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("1"));
                        flag = 1;
                    }
                }
                if((output_array[2]>>2)&0x1 == 1)
                {
                    if(flag)
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("/2"));
                    else
                    {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("2"));
                        flag = 1;
                    }
                }
                if((output_array[2]>>3)&0x1 == 1)
                {
                    if(flag)
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("/3"));
                    else
                    {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("3"));
                        flag = 1;
                    }
                }
                if((output_array[2]>>4)&0x1 == 1)
                {
                    if(flag)
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("/4"));
                    else
                    {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("4"));
                        flag = 1;
                    }
                }
                if((output_array[2]>>5)&0x1 == 1)
                {
                    if(flag)
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("/5"));
                    else
                    {
                        ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("5"));
                        flag = 1;
                    }
                }
                if(flag)
                {
                    ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("故障"));
                }
                else
                {
                    ui->tableWidget->item(0,1)->setText(ui->tableWidget->item(0,1)->text()+tr("正常"));
                }
            }
            break;
        case 0x02:
            switch(output_array[1])
            {
                case 0x20:
                    respstat.osdcolor = 1;
                    break;
                case 0x21:
                    respstat.osdfont = 1;
                    break;
                case 0x22:
                    respstat.osdsize = 1;
                    break;
                default:
                    break;
            }
            ui->tableWidget->item(1,1)->setText(tr("命令")+tr("0x")+QString("%1").arg(output_array[1],2,16,QLatin1Char('0'))+tr("执行成功"));
            break;
        case 0x03:
            switch(output_array[1])
            {
                case 0x20:
                    respstat.osdcolor = 1;
                    break;
                case 0x21:
                    respstat.osdfont = 1;
                    break;
                case 0x22:
                    respstat.osdsize = 1;
                    break;
                default:
                    break;
            }
            ui->tableWidget->item(2,1)->setText(tr("命令")+tr("0x")+QString("%1").arg(output_array[1],2,16,QLatin1Char('0'))+tr("执行失败"));
            break;
        case 0x04:
            respstat.sensor = 1;
            ui->tableWidget->item(3,1)->setText(tr("通道")+QString("%1").arg(output_array[1]));
            break;
        case 0x05:
            respstat.sensor_bind = 1;
            ui->tableWidget->item(4,1)->setText(tr("通道")+QString("%1").arg(output_array[1]));
            break;
        case 0x06:
            respstat.trk = 1;
            if(0x01 == output_array_6[1])
            {
                ui->tableWidget->item(5,1)->setText(tr("捕获"));
            }
            else if(0x02 == output_array_6[1])
            {
                ui->tableWidget->item(5,1)->setText(tr("跟踪"));
            }
            break;
        case 0x07:
            respstat.trk = 2;
            if(0x01 == output_array_7[1])
                ui->tableWidget->item(6,1)->setText(tr("正常跟踪"));
            else if(0x02 == output_array_7[1])
                ui->tableWidget->item(6,1)->setText(tr("记忆跟踪"));
            else if(0x03 == output_array_7[1])
                ui->tableWidget->item(6,1)->setText(tr("目标丢失"));
            break;
        case 0x08:
            trkerrx = (output_array_8[1]|(output_array_8[2]<<8));
            trkerry = (output_array_8[3]|(output_array_8[4]<<8));
            ui->tableWidget->item(7,1)->setText(tr("x,y(")+QString("%1").arg(trkerrx)+tr(",")+QString("%1").arg(trkerry)+tr(")"));
            break;
        case 0x09:
            respstat.mmt = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(8,1)->setText(tr("开启"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(8,1)->setText(tr("关闭"));
            break;
        case 0x0a:
            respstat.mmtselect = 1;
            ui->tableWidget->item(9,1)->setText(tr("编号")+QString("%1").arg(output_array[1]));
            break;
        case 0x0b:
            respstat.enh = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(10,1)->setText(tr("开启"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(10,1)->setText(tr("关闭"));
            break;
        case 0x0c:
            respstat.posmove = 1;
            ui->tableWidget->item(11,1)->setText("");
            if(0x01 == output_array[1])
                ui->tableWidget->item(11,1)->setText(tr("左"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(11,1)->setText(tr("右"));
            if(0x01 == output_array[2])
                ui->tableWidget->item(11,1)->setText(ui->tableWidget->item(11,1)->text()+tr("上"));
            else if(0x02 == output_array[2])
                ui->tableWidget->item(11,1)->setText(ui->tableWidget->item(11,1)->text()+tr("下"));
            break;
        case 0x0d:
            respstat.axismove = 1;
            ui->tableWidget->item(0,3)->setText("");
            if(0x01 == output_array[1])
                ui->tableWidget->item(0,3)->setText(tr("左"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(0,3)->setText(tr("右"));
            if(0x01 == output_array[2])
                ui->tableWidget->item(0,3)->setText(ui->tableWidget->item(0,3)->text()+tr("上"));
            else if(0x02 == output_array[2])
                ui->tableWidget->item(0,3)->setText(ui->tableWidget->item(0,3)->text()+tr("下"));
            break;
        case 0x0e:
            respstat.zoom = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(1,3)->setText(tr("2倍"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(1,3)->setText(tr("4倍"));
            else if(0x03 == output_array[1])
                ui->tableWidget->item(1,3)->setText(tr("8倍"));
            else if(0x04 == output_array[1])
                ui->tableWidget->item(1,3)->setText(tr("不变倍"));
            break;
        case 0x0f:
            respstat.sectrk = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(2,3)->setText(tr("打开"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(2,3)->setText(tr("关闭"));
            break;
        case 0x10:
            respstat.mtd = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(3,3)->setText(tr("开启"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(3,3)->setText(tr("关闭"));
            break;
        case 0x11:
            respstat.pinp = 1;
            if(0x01 == output_array[1])
            {
                ui->tableWidget->item(4,3)->setText(tr("开启，子画面通道")+QString("%1").arg(output_array[2]));
            }
            else if(0x02 == output_array[1])
            {
                ui->tableWidget->item(4,3)->setText(tr("关闭"));
            }
            break;
        case 0x20:
            respstat.sensor_trans = 1;
            ui->tableWidget->item(5,3)->setText(tr("通道")+QString("%1").arg(output_array[1]));
            break;
        case 0x21:
            respstat.vframerate = 1;
            ui->tableWidget->item(6,3)->setText(tr("通道")+QString("%1").arg(output_array[2])+tr("帧频:")+QString("%1").arg(output_array[1]));
            break;
        case 0x22:
            respstat.vquality = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(7,3)->setText(tr("通道")+QString("%1").arg(output_array[2])+tr("低质量"));
            else if(0x02 == output_array[1])
                ui->tableWidget->item(7,3)->setText(tr("通道")+QString("%1").arg(output_array[2])+tr("标准质量"));
            else if(0x03 == output_array[1])
                ui->tableWidget->item(7,3)->setText(tr("通道")+QString("%1").arg(output_array[2])+tr("高质量"));
            break;
        case 0x30:
            respstat.setconfig = 1;
            memcpy(&value1, (const void *)(output_array+3), 4);
            ui->tableWidget->item(8,3)->setText(tr("块:")+QString("%1").arg(output_array[1])+tr(",域:")+QString("%1").arg(output_array[2])+tr("值:")+QString("%1").arg(value1));
            break;
        case 0x31:
            respstat.getconfig = 1;
            memcpy(&value2, (const void *)(output_array+3), 4);
            ui->tableWidget->item(9,3)->setText(tr("块:")+QString("%1").arg(output_array[1])+tr(",域:")+QString("%1").arg(output_array[2])+tr("值:")+QString("%1").arg(value2));
            break;
        case 0x32:
            respstat.joyskeyboard = 1;
            if((output_array[3]>>7)&0x1)
                ui->tableWidget->item(10,3)->setText(tr("键")+QString("%1").arg(output_array[3]&0x7f)+tr("按下")+tr(",")+tr("x,y,z(")+QString("%1").arg(output_array[4]|(output_array[5]<<8))+tr(",")+QString("%1").arg(output_array[6]|(output_array[7]<<8))+tr(",")+QString("%1").arg(output_array[8]|(output_array[9]<<8))+tr(")"));
            else
                ui->tableWidget->item(10,3)->setText(tr("键")+QString("%1").arg(output_array[3]&0x7f)+tr("抬起")+tr(",")+tr("x,y,z(")+QString("%1").arg(output_array[4]|(output_array[5]<<8))+tr(",")+QString("%1").arg(output_array[6]|(output_array[7]<<8))+tr(",")+QString("%1").arg(output_array[8]|(output_array[9]<<8))+tr(")"));
            break;
        case 0x34:
            respstat.saveconfig = 1;
            if(0x01 == output_array[1])
                ui->tableWidget->item(11,3)->setText("保存成功");
            else if(0x02 == output_array[1])
                ui->tableWidget->item(11,3)->setText("保存失败");
            break;
        default:
            break;
    }
}

void Dialog::load_profile()
{
    int i = 0;
    QString displayString;
    QFile file("Profile.yml");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
        if(str.startsWith("cfg_avt_"))
        {
            if(i<16){
            tableWidget_Profile->setItem(i,0, new QTableWidgetItem(string_config[i]));
            tableWidget_Profile->setItem(i,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }else{
                break;
            }
            i++;
        }
    }
}
void Dialog::load_camera_profile()
{
    int i = 0;
    QString displayString;
    QFile file("camera_Profile.yml");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
        if(str.startsWith("cfg_avt_"))
        {
            if(i<16){
            tabWidget_CameraParam1_camera_Profile->setItem(i,0, new QTableWidgetItem(str.section(':', 0, 0).trimmed()));
            tabWidget_CameraParam1_camera_Profile->setItem(i,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }else{
                break;
            }
            i++;
        }
    }

}
void Dialog::check_iftimeout()
{
    switch(send_arr[3])
    {
        case 0x01:
            if(!respstat.autocheck)
                QMessageBox::warning(NULL, tr("提示"), tr("启动自检响应超时！"), QMessageBox::Close);
            break;
        case 0x02:
            if(!respstat.sensor)
                QMessageBox::warning(NULL, tr("提示"), tr("主视频通道选择响应超时！"), QMessageBox::Close);
            break;
        case 0x03:
            if(!respstat.sensor_bind)
                QMessageBox::warning(NULL, tr("提示"), tr("通道绑定响应超时！"), QMessageBox::Close);
            break;
        case 0x04:
            if(!respstat.trk)
                QMessageBox::warning(NULL, tr("提示"), tr("跟踪命令响应超时！"), QMessageBox::Close);
            break;
        case 0x05:
            if(!respstat.mmt)
                QMessageBox::warning(NULL, tr("提示"), tr("多目标提示响应超时！"), QMessageBox::Close);
            break;
        case 0x06:
            if(!respstat.mmtselect)
                QMessageBox::warning(NULL, tr("提示"), tr("多目标编号选择响应超时！"), QMessageBox::Close);
            break;
        case 0x07:
            if(!respstat.enh)
                QMessageBox::warning(NULL, tr("提示"), tr("图像增强响应超时！"), QMessageBox::Close);
            break;
        case 0x08:
            if(!respstat.posmove)
                QMessageBox::warning(NULL, tr("提示"), tr("跟踪微调响应超时！"), QMessageBox::Close);
            break;
        case 0x09:
            if(!respstat.axismove)
                QMessageBox::warning(NULL, tr("提示"), tr("校轴响应超时！"), QMessageBox::Close);
            break;
        case 0x0a:
            if(!respstat.zoom)
                QMessageBox::warning(NULL, tr("提示"), tr("电子变倍响应超时！"), QMessageBox::Close);
            break;
        case 0x0b:
            if(!respstat.sectrk)
                QMessageBox::warning(NULL, tr("提示"), tr("跟搜控制响应超时！"), QMessageBox::Close);
            break;
        case 0x0d:
            if(!respstat.mtd)
                QMessageBox::warning(NULL, tr("提示"), tr("运动目标检测响应超时！"), QMessageBox::Close);
            break;
        case 0x0e:
            if(!respstat.pinp)
                QMessageBox::warning(NULL, tr("提示"), tr("画中画响应超时！"), QMessageBox::Close);
            break;
        case 0x0f:
            if(!respstat.sensor_trans)
                QMessageBox::warning(NULL, tr("提示"), tr("选择传输视频通道响应超时！"), QMessageBox::Close);
            break;
        case 0x10:
            if(!respstat.vframerate)
                QMessageBox::warning(NULL, tr("提示"), tr("帧频控制响应超时！"), QMessageBox::Close);
            break;
        case 0x11:
            if(!respstat.vquality)
                QMessageBox::warning(NULL, tr("提示"), tr("压缩质量响应超时！"), QMessageBox::Close);
            break;
        case 0x20:
            if(!respstat.osdcolor)
                QMessageBox::warning(NULL, tr("提示"), tr("字符颜色响应超时！"), QMessageBox::Close);
            break;
        case 0x21:
            if(!respstat.osdfont)
                QMessageBox::warning(NULL, tr("提示"), tr("字符字体响应超时！"), QMessageBox::Close);
            break;
        case 0x22:
            if(!respstat.osdsize)
                QMessageBox::warning(NULL, tr("提示"), tr("字号大小响应超时！"), QMessageBox::Close);
            break;
        case 0x30:
            if(!respstat.setconfig)
                QMessageBox::warning(NULL, tr("提示"), tr("设置命令响应超时！"), QMessageBox::Close);
            break;
        case 0x31:
            if(!respstat.getconfig)
                QMessageBox::warning(NULL, tr("提示"), tr("读命令响应超时！"), QMessageBox::Close);
            break;
        case 0x32:
            if(!respstat.joyskeyboard)
                QMessageBox::warning(NULL, tr("提示"), tr("手柄键盘命令响应超时！"), QMessageBox::Close);
            break;
        case 0x33:
            //if(!respstat.downconfig)
             //   QMessageBox::warning(NULL, tr("提示"), tr("下载配置响应超时！"), QMessageBox::Close);
            break;
        case 0x34:
            if(!respstat.saveconfig)
                QMessageBox::warning(NULL, tr("提示"), tr("保存配置响应超时！"), QMessageBox::Close);
            break;
        default:
            break;

    }
    send_timer->stop();
}


void Dialog::on_lineEdit_jiaoju_editingFinished()
{
    unsigned short jiaoju = ui->lineEdit_jiaoju->text().toUShort();
    send_mutex.lock();
    send_arr[3] = 0x40;
    send_arr[4] = (jiaoju&0xff);
    send_arr[5] = ((jiaoju>>8)&0xff);;
    send_oneframe(7);
    send_mutex.unlock();
}
void Dialog::on_pushButton_setconf_clicked()
{
    int block = ui->lineEdit_block->text().toInt();
    int field = ui->lineEdit_field->text().toInt();
    float value = ui->lineEdit_value->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = block;
    send_arr[5] = field;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}
void Dialog::on_pushButton_getconf_clicked()
{
    int gblock = ui->lineEdit_gblock->text().toInt();
    int gfield = ui->lineEdit_gfield->text().toInt();
    send_mutex.lock();
    send_arr[3] = 0x31;
    send_arr[4] = gblock;
    send_arr[5] = gfield;
    send_arr[6] = 0;
    send_arr[7] = 0;
    send_arr[8] = 0;
    send_arr[9] = 0;
    send_oneframe(11);
    send_mutex.unlock();
}
void Dialog::onMsgB()
{
    send_mutex.lock();
    send_arr[3] = 0x34;
    send_oneframe(5);
    send_mutex.unlock();
    //QMessageBox msgBox;
    //msgBox.setText("qzher.com  menu test!!!");
    //msgBox.exec();
}
void Dialog::onMsgD()
{
    load_config_flag = 1;
    load_profile();
    load_camera_profile();
    load_config_flag = 0;
}
void Dialog::onMsgE()
{
    this->close();
}
void Dialog::onMsgF()
{
    dialog_config.close();
}
void Dialog::onMsgG()
{
    dialog_joys.show();
}

void Dialog::init_dialog_joys()
{
    dialog_joys.setWindowTitle(tr("手柄"));
    dialog_joys.setGeometry(QRect(1170, 123, 240, 330));
    tableWidget_joys = new QTableWidget();
    tableWidget_joys->setFixedWidth(212);
    tableWidget_joys->setFixedHeight(261);
    tableWidget_joys->setRowCount(13);
    tableWidget_joys->setColumnCount(2);
    tableWidget_joys->setColumnWidth(0,110);
    for(int m = 0; m<13; m++)
        tableWidget_joys->setRowHeight(m,18);
    tableWidget_joys->setHorizontalHeaderLabels(QStringList()<<tr("Item")<<tr("Value"));
    QHeaderView* headerView = tableWidget_joys->verticalHeader();
    headerView->setHidden(true);//隐藏竖直方向的表头
    tableWidget_joys->setItem(0,0, new QTableWidgetItem("dwSize"));
    tableWidget_joys->setItem(1,0, new QTableWidgetItem("dwFlags"));
    tableWidget_joys->setItem(2,0, new QTableWidgetItem("dwXpos"));
    tableWidget_joys->setItem(3,0, new QTableWidgetItem("dwYpos"));
    tableWidget_joys->setItem(4,0, new QTableWidgetItem("dwZpos"));
    tableWidget_joys->setItem(5,0, new QTableWidgetItem("dwRpos"));
    tableWidget_joys->setItem(6,0, new QTableWidgetItem("dwUpos"));
    tableWidget_joys->setItem(7,0, new QTableWidgetItem("dwVpos"));
    tableWidget_joys->setItem(8,0, new QTableWidgetItem("dwButtons"));
    tableWidget_joys->setItem(9,0, new QTableWidgetItem("dwButtonNumber"));
    tableWidget_joys->setItem(10,0, new QTableWidgetItem("dwPOV"));
    tableWidget_joys->setItem(11,0, new QTableWidgetItem("dwReserved1"));
    tableWidget_joys->setItem(12,0, new QTableWidgetItem("dwReserved2"));

    tableWidget_joys->setItem(0,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(1,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(2,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(3,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(4,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(5,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(6,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(7,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(8,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(9,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(10,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(11,1, new QTableWidgetItem(""));
    tableWidget_joys->setItem(12,1, new QTableWidgetItem(""));

    openjoys = new QPushButton();
    closejoys = new QPushButton();
    openjoys->setText("打开手柄");
    closejoys->setText("关闭手柄");
    openjoys->setEnabled(true);
    closejoys->setEnabled(false);
    connect(openjoys, SIGNAL(clicked()), this, SLOT(openJoy()));
    connect(closejoys, SIGNAL(clicked()), this, SLOT(closeJoy()));

    horizontalSlider = new QSlider();
    horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
    horizontalSlider->setMaximum(65535);
    horizontalSlider->setOrientation(Qt::Horizontal);

    POVU = new QPushButton();
    POVUR = new QPushButton();
    POVR = new QPushButton();
    POVDR = new QPushButton();
    POVD = new QPushButton();
    POVDL = new QPushButton();
    POVL = new QPushButton();
    POVUL = new QPushButton();
    POVCEN = new QPushButton();
    POVU->setText("上");
    POVUR->setText("右上");
    POVR->setText("右");
    POVDR->setText("右下");
    POVD->setText("下");
    POVDL->setText("左下");
    POVL->setText("左");
    POVUL->setText("左上");
    POVCEN->setText("中");
    POVU->setFixedWidth(31);
    POVU->setFixedHeight(23);
    POVUR->setFixedWidth(31);
    POVUR->setFixedHeight(23);
    POVR->setFixedWidth(31);
    POVR->setFixedHeight(23);
    POVDR->setFixedWidth(31);
    POVDR->setFixedHeight(23);
    POVD->setFixedWidth(31);
    POVD->setFixedHeight(23);
    POVDL->setFixedWidth(31);
    POVDL->setFixedHeight(23);
    POVL->setFixedWidth(31);
    POVL->setFixedHeight(23);
    POVUL->setFixedWidth(31);
    POVUL->setFixedHeight(23);
    POVCEN->setFixedWidth(31);
    POVCEN->setFixedHeight(23);
    POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
    POVCEN->setStyleSheet("background-color: rgb(170, 170, 170);");

    J1 = new QPushButton();
    J2 = new QPushButton();
    J3 = new QPushButton();
    J4 = new QPushButton();
    J5 = new QPushButton();
    J6 = new QPushButton();
    J7 = new QPushButton();
    J8 = new QPushButton();
    J9 = new QPushButton();
    J10 = new QPushButton();
    J11 = new QPushButton();
    J12 = new QPushButton();
    J1->setText("1");
    J2->setText("2");
    J3->setText("3");
    J4->setText("4");
    J5->setText("5");
    J6->setText("6");
    J7->setText("7");
    J8->setText("8");
    J9->setText("9");
    J10->setText("10");
    J11->setText("11");
    J12->setText("12");
    J1->setFixedWidth(31);
    J1->setFixedHeight(23);
    J2->setFixedWidth(31);
    J2->setFixedHeight(23);
    J3->setFixedWidth(31);
    J3->setFixedHeight(23);
    J4->setFixedWidth(31);
    J4->setFixedHeight(23);
    J5->setFixedWidth(31);
    J5->setFixedHeight(23);
    J6->setFixedWidth(31);
    J6->setFixedHeight(23);
    J7->setFixedWidth(31);
    J7->setFixedHeight(23);
    J8->setFixedWidth(31);
    J8->setFixedHeight(23);
    J9->setFixedWidth(31);
    J9->setFixedHeight(23);
    J10->setFixedWidth(31);
    J10->setFixedHeight(23);
    J11->setFixedWidth(31);
    J11->setFixedHeight(23);
    J12->setFixedWidth(31);
    J12->setFixedHeight(23);
    J1->setStyleSheet("background-color: rgb(210, 210, 210);");
    J2->setStyleSheet("background-color: rgb(210, 210, 210);");
    J3->setStyleSheet("background-color: rgb(210, 210, 210);");
    J4->setStyleSheet("background-color: rgb(210, 210, 210);");
    J5->setStyleSheet("background-color: rgb(210, 210, 210);");
    J6->setStyleSheet("background-color: rgb(210, 210, 210);");
    J7->setStyleSheet("background-color: rgb(210, 210, 210);");
    J8->setStyleSheet("background-color: rgb(210, 210, 210);");
    J9->setStyleSheet("background-color: rgb(210, 210, 210);");
    J10->setStyleSheet("background-color: rgb(210, 210, 210);");
    J11->setStyleSheet("background-color: rgb(210, 210, 210);");
    J12->setStyleSheet("background-color: rgb(210, 210, 210);");

    connect(J1, SIGNAL(pressed()), this, SLOT(on_J1_pressed()));
    /*connect(J2, SIGNAL(pressed()), this, SLOT(on_J1_pressed()));
    connect(J3, SIGNAL(pressed()), this, SLOT(on_J2_pressed()));
    connect(J4, SIGNAL(pressed()), this, SLOT(on_J3_pressed()));
    connect(J5, SIGNAL(pressed()), this, SLOT(on_J4_pressed()));
    connect(J6, SIGNAL(pressed()), this, SLOT(on_J5_pressed()));
    connect(J7, SIGNAL(pressed()), this, SLOT(on_J6_pressed()));
    connect(J8, SIGNAL(pressed()), this, SLOT(on_J7_pressed()));
    connect(J9, SIGNAL(pressed()), this, SLOT(on_J8_pressed()));
    connect(J10, SIGNAL(pressed()), this, SLOT(on_J9_pressed()));
    connect(J11, SIGNAL(pressed()), this, SLOT(on_J10_pressed()));
    connect(J12, SIGNAL(pressed()), this, SLOT(on_J11_pressed()));*/
    connect(J1, SIGNAL(released()), this, SLOT(on_J1_released()));


    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    QFormLayout *pLayout = new QFormLayout();
    QGridLayout *gLayout = new QGridLayout();
    QHBoxLayout *hlayout_main = new QHBoxLayout;

    hlayout->addWidget(openjoys);
    hlayout->addWidget(closejoys);
    pLayout->addRow(QStringLiteral("Z轴:"), horizontalSlider);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(tableWidget_joys);
    vlayout->addLayout(pLayout);

    gLayout->addWidget(POVUL,0,0,1,1);
    gLayout->addWidget(POVU,0,1,1,1);
    gLayout->addWidget(POVUR,0,2,1,1);
    gLayout->addWidget(POVL,1,0,1,1);
    gLayout->addWidget(POVCEN,1,1,1,1);
    gLayout->addWidget(POVR,1,2,1,1);
    gLayout->addWidget(POVDL,2,0,1,1);
    gLayout->addWidget(POVD,2,1,1,1);
    gLayout->addWidget(POVDR,2,2,1,1);
    gLayout->addWidget(J1,3,0,1,1);
    gLayout->addWidget(J2,3,1,1,1);
    gLayout->addWidget(J3,3,2,1,1);
    gLayout->addWidget(J4,4,0,1,1);
    gLayout->addWidget(J5,4,1,1,1);
    gLayout->addWidget(J6,4,2,1,1);
    gLayout->addWidget(J7,5,0,1,1);
    gLayout->addWidget(J8,5,1,1,1);
    gLayout->addWidget(J9,5,2,1,1);
    gLayout->addWidget(J10,6,0,1,1);
    gLayout->addWidget(J11,6,1,1,1);
    gLayout->addWidget(J12,6,2,1,1);

    hlayout_main->addLayout(vlayout);
    hlayout_main->addLayout(gLayout);
    dialog_joys.setLayout(hlayout_main);
}

void Dialog::on_J1_pressed()
{
#if 0
    int x = (a-POINTX+WIDTH/RATIO/2)*65535*RATIO/WIDTH;
    int y = (b-POINTX+HEIGHT/RATIO/2)*65535*RATIO/HEIGHT;
    unsigned short z = horizontalSlider->value();
    send_mutex.lock();
    send_arr[3] = 0x32;
    send_arr[4] = 0x00;
    send_arr[5] = 0x00;
    send_arr[6] = 0x00;
    send_arr[6] |= 0;
    send_arr[6] |= (1<<7);
    send_arr[7] = (x&0xff);
    send_arr[8] = ((x>>8)&0xff);
    send_arr[9] |= (y&0xff);
    send_arr[10] = ((y>>8)&0xff);
    send_arr[11] = (z&0xff);
    send_arr[12] = ((z>>8)&0xff);
    send_arr[13] = (old_pov&0xff);
    send_arr[14] = ((old_pov>>8)&0xff);
    send_oneframe(16);
    send_mutex.unlock();
#endif
}
void Dialog::on_J1_released()
{
#if 0
    int x = (a-POINTX+WIDTH/RATIO/2)*65535*RATIO/WIDTH;
    int y = (b-POINTX+HEIGHT/RATIO/2)*65535*RATIO/HEIGHT;
    unsigned short z = horizontalSlider->value();
    send_mutex.lock();
    send_arr[3] = 0x32;
    send_arr[4] = 0x00;
    send_arr[5] = 0x00;
    send_arr[6] = 0x00;
    send_arr[6] |= 0;
    send_arr[6] &= ~(1<<7);
    send_arr[7] = (x&0xff);
    send_arr[8] = ((x>>8)&0xff);
    send_arr[9] |= (y&0xff);
    send_arr[10] = ((y>>8)&0xff);
    send_arr[11] = (z&0xff);
    send_arr[12] = ((z>>8)&0xff);
    send_arr[13] = (old_pov&0xff);
    send_arr[14] = ((old_pov>>8)&0xff);
    send_oneframe(16);
    send_mutex.unlock();
#endif
}




