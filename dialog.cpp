#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include "QMenuBar"
#include "QDialogButtonBox"
#include "QVBoxLayout"
#include <QMessageBox>
#include <QTimer>
#include "joystick.h"

#include<QDataStream>
#include<cstdio>
#include <QFile>
#include<QButtonGroup>
#include "QAction"
#include "QFileDialog"
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QStringList>
#include<QComboBox>
#include<QColor>
#include<QMutex>
#include<QTime>
#include <QTableWidget>
#include "qpainter.h"
#include "QMouseEvent"
#include "QMenu"


extern volatile bool thread_run;
extern volatile bool thread_run_socket;
QString show_str;
int joystick_flag = 0;

typedef enum
{
    curpov_cen,
    curpov_u,
    curpov_ur,
    curpov_r,
    curpov_dr,
    curpov_d,
    curpov_dl,
    curpov_l,
    curpov_ul,
}current_pov;

int current_povstat = curpov_cen;

Dialog::Dialog(enum MODE mode,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    for(int i = 0; i < 16; i++)//new
    {
        m_button[i] = 0;
    }
    old_xPos = 32767;
    old_yPos = 32767;
    old_zPos = 0;
    old_pov = JOY_POVCENTERED;
    pov_forward = false;
    pov_backward = false;
    pov_left = false;
    pov_right = false;
    pov_center = true;
    m_mode = mode;
    sqmax = 32767*1.15;//37682
    sqmin = 32767*0.85;//27852

    ui->setupUi(this);
    this->setWindowTitle(tr("VT322 V1.3"));//设置显示框的名字
    //this->resize(714,614);
    this->setMaximumSize(714,614);
    this->setMinimumSize(714,614);
    a=POINTX;b=POINTY;m_dragging = 0;//a,b为起始坐标点
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(joyMove()));

    joyXPos = 0;
    joyYPos = 0;
    joyZPos = 0;
    joyRPos = 0;
    joyUPos = 0;
    joyVPos = 0;
    joyX = 0;
    joyY = 0;
    joyZ = 0;
    joyR = 0;
    joyU = 0;
    joyV = 0;
    hasV = false;
    numButtons = 0;
    numAxes = 0;

    load_config_flag = 0;
    init_menu();
    init_dialog_sys();
    init_table();

    //------------
    serialPort_command = new QSerialPort(this);
    connect(this,&Dialog::copy_Done, this ,&Dialog::parse_bytearray);


    thread_01 = new RcvSerialdata(this);//定义一个线程对象（接收）
    connect(thread_01,&RcvSerialdata::send2main_signal, this, &Dialog::output_to_label);
    connect(this,&Dialog::destroyed, this,&Dialog::stop_thread_now);
    thread_run = true;
    thread_01->start();

    socket = new QTcpSocket();
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Dialog::socket_Read_Data);
    connect(this,&Dialog::socket_copy_Done, this ,&Dialog::socket_parse_bytearray);
    thread_socket = new RcvSocketdata(this);
    connect(thread_socket,&RcvSocketdata::socket2main_signal, this, &Dialog::output_to_label);
    thread_run_socket = true;
    thread_socket->start();

    init_dialog();

    send_timer = new QTimer(this);
    connect(send_timer,&QTimer::timeout  ,this,&Dialog::check_iftimeout);
    timeval_select = 50;



    init_dialog_joys();
    this->setMouseTracking ( true);
}

Dialog::~Dialog()
{
    delete ui;
    delete serialPort_command;
    delete this->socket;
    delete send_timer;
}

void Dialog::on_pushButton_model_clicked()
{
    qDebug() << "NormalBtn_Clicked() Begin";
    QDialog* dialog = new QDialog(this);//如定义为栈  QDialog dialog ；  dialog->show();会一闪而过  也就是说对话框显示至桌面时，依然会继续往下运行，运行到函数的末尾（这个是消息映射函数）局部变量就被销毁了，所以对话框就消失了  如果是在堆上，销毁的只是指向这个堆对象的指针，堆对象不会被销毁，对话框就不糊消失了
    dialog->setAttribute(Qt::WA_DeleteOnClose);//设置该属性即可在让在该窗口关闭时就可以释放堆上的内存了不会造成泄漏
    dialog->show();
    // done(Rejected);
    qDebug() << "NormalBtn_Clicked() End";
}

void Dialog::on_pushButton_normal_clicked()
{
    qDebug() << "NormalBtn_Clicked() Begin";
    QDialog* dialog = new QDialog(this);//如定义为栈  QDialog dialog ；  dialog->show();会一闪而过  也就是说对话框显示至桌面时，依然会继续往下运行，运行到函数的末尾（这个是消息映射函数）局部变量就被销毁了，所以对话框就消失了  如果是在堆上，销毁的只是指向这个堆对象的指针，堆对象不会被销毁，对话框就不糊消失了
    dialog->setAttribute(Qt::WA_DeleteOnClose);//设置该属性即可在让在该窗口关闭时就可以释放堆上的内存了不会造成泄漏
    dialog->show();
    // done(Rejected);
    qDebug() << "NormalBtn_Clicked() End";
}

void Dialog::on_pushButton_mixed_clicked()
{
    qDebug() << "MixedBtn_Clicked() Begin";
    QDialog* dialog = new QDialog(this);//指定父组件this
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setModal(true);//设置非模态对话框的行为类似模态对话框   为混合对话框
    dialog->show();
    // done(100);
    qDebug() << "MixedBtn_Clicked() End";
}
void Dialog::on_pushButton_lastpage_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void Dialog::stop_thread_now()  // 当点击窗口右上角的关闭按钮时，会自动触发MyWidget的destroyed信号，
{                              // 使用connect与其绑定此函数：在关闭窗口时若有线程正在运行则先退出线程再关闭窗口；
    if(thread_01->isRunning()){
        thread_run = false;
        thread_01->quit();
        thread_01->wait();
    }
    if(thread_socket->isRunning()){
        thread_run_socket = false;
        thread_socket->quit();
        thread_socket->wait();
    }
}

int Dialog::openJoy(){
    unsigned int num = qJoyGetNumDevs();//取当前计算机中有多少游戏手柄
    if(num <= 0)
    {
        ui->label_showmsg->setText("");
        return -1;
    }

    JOYCAPS joycaps;
    UINT size = (UINT)sizeof(joycaps);
    qJoyGetDevCaps(JOYSTICKID1, &joycaps, size); //获取操纵杆属性信息，以结构体JoyCaps接收。
    numButtons = joycaps.wNumButtons;//按钮数
    numAxes = joycaps.wNumAxes;
    //ui->label_8->setNum(numButtons);
    //ui->label_9->setNum(numAxes);
    unsigned int caps = joycaps.wCaps;
    if(caps & JOYCAPS_HASV) hasV = true;
    if(caps & JOYCAPS_HASU) hasU = true;
    //if(caps & JOYCAPS_HASPOV) ui->label_haspov->setText(QString("has JOYCAPS_HASPOV."));
    //if(caps & JOYCAPS_POV4DIR) ui->label_pov4dir->setText(QString("has JOYCAPS_POV4DIR."));
    //if(caps & JOYCAPS_POVCTS) ui->label_povcts->setText(QString("has JOYCAPS_POVCTS."));
    openjoys->setEnabled(false);
    closejoys->setEnabled(true);
    timer->start();
}
void Dialog::closeJoy(){
    openjoys->setEnabled(true);
    closejoys->setEnabled(false);
    timer->stop();
}

void Dialog::POV_StateMachine_Axis(int pov)
{
    if(pov != old_pov)
    {
        if( pov == JOY_POVFORWARD )
        {
            qDebug("up\n");
            current_povstat = curpov_u;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");

        }
        if( pov == JOY_POVFORWARD + 4500 )
        {
            qDebug("up right\n");
            current_povstat = curpov_ur;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVRIGHT )
        {
            qDebug("right\n");
            current_povstat = curpov_r;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVRIGHT  + 4500 )
        {
            qDebug("down right\n");
            current_povstat = curpov_dr;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVBACKWARD )
        {
            qDebug("down\n");
            current_povstat = curpov_d;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVBACKWARD + 4500 )
        {
            qDebug("down left\n");
            current_povstat = curpov_dl;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVLEFT )
        {
            qDebug("left\n");
            current_povstat = curpov_l;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVLEFT + 4500 )
        {
            qDebug("up left\n");
            current_povstat = curpov_ul;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(170, 170, 170);");
            POVCEN->setStyleSheet("background-color: rgb(210, 210, 210);");
        }
        if( pov == JOY_POVCENTERED )
        {
            qDebug("center\n");
            current_povstat = curpov_cen;
            joystick_flag = 1;
            send_mutex.lock();
            send_arr[13] = (pov&0xff);
            send_arr[14] = ((pov>>8)&0xff);
            send_mutex.unlock();
            POVU->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDR->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVD->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVDL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVUL->setStyleSheet("background-color: rgb(210, 210, 210);");
            POVCEN->setStyleSheet("background-color: rgb(170, 170, 170);");
        }
        old_pov = pov;
    }
}

void Dialog::Button_StateMachine(int button)
{
    const int mask[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
    for(int i = 0; i < 12; i++)
    {
        int n = button & mask[i];
        if(n ^ m_button[i])
        {
            m_button[i] = n;
            if( n )
            {
                qDebug() << "ButtonPressed(" << i + 1 << ")";
                joystick_flag = 1;
                send_mutex.lock();
                send_arr[6] = 0x00;
                send_arr[6] |= i;
                send_arr[6] |= (1<<7);
                send_mutex.unlock();
                switch(i+1)
                {
                    case 1:
                        J1->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 2:
                        J2->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 3:
                        J3->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 4:
                        J4->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 5:
                        J5->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 6:
                        J6->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 7:
                        J7->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 8:
                        J8->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 9:
                        J9->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 10:
                        J10->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 11:
                        J11->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    case 12:
                        J12->setStyleSheet("background-color: rgb(170, 170, 170);");
                        break;
                    default:
                        break;
                }
            }
            else
            {
                qDebug() << "ButtonReleased(" << i + 1 << ")";
                joystick_flag = 1;
                send_mutex.lock();
                send_arr[6] = 0x00;
                send_arr[6] |= i;
                send_arr[6] &= ~(1<<7);
                send_mutex.unlock();
                switch(i+1)
                {
                    case 1:
                        J1->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 2:
                        J2->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 3:
                        J3->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 4:
                        J4->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 5:
                        J5->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 6:
                        J6->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 7:
                        J7->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 8:
                        J8->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 9:
                        J9->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 10:
                        J10->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 11:
                        J11->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    case 12:
                        J12->setStyleSheet("background-color: rgb(210, 210, 210);");
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            if(6 == (i+1))
            {
                if(n)
                {
                    //qDebug()<<"button6 still pressed";

                }
                else
                {

                }
            }
        }
    }
}

void Dialog::Coordinate_StateMachine(int xPos, int yPos)
{
    //if((xPos>(32767*0.85))&&(xPos<(32767*1.15)))
    if((xPos>sqmin)&&(xPos<sqmax))
        xPos = 32767;
    //if((yPos>(32767*0.85))&&(yPos<(32767*1.15)))
    if((yPos>sqmin)&&(yPos<sqmax))
        yPos = 32767;
    if(xPos == old_xPos && yPos == old_yPos)
    {
        //qDebug()<<"x,y not change";
        return;
    }
    joystick_flag = 1;
    send_mutex.lock();
    send_arr[7] = (xPos&0xff);
    send_arr[8] = ((xPos>>8)&0xff);
    send_arr[9] |= (yPos&0xff);
    send_arr[10] = ((yPos>>8)&0xff);
    send_mutex.unlock();
    old_xPos = xPos;
    old_yPos = yPos;
    a = POINTX-WIDTH/RATIO/2+xPos*WIDTH/RATIO/65535;
    b = POINTY-HEIGHT/RATIO/2+yPos*HEIGHT/RATIO/65535;
    ui->label_xy->setText(tr("(")+QString::number(xPos)+","+QString::number(yPos)+")");
    //repaint();
    update();
}

void Dialog::Coordinate_zStateMachine(int zPos)
{
    if(zPos == old_zPos)
    {
        //qDebug()<<"x,y not change";
        return;
    }
    horizontalSlider->setValue(zPos);
    joystick_flag = 1;
    send_mutex.lock();
    send_arr[11] = (zPos&0xff);
    send_arr[12] = ((zPos>>8)&0xff);
    send_mutex.unlock();
    old_zPos = zPos;
}

void Dialog::AxisX_StateMachine(int xPos)
{
    if(xPos == old_xPos) return;
    switch(xPos)
    {
    case 0:
        qDebug()<<"Joy_MoveLeft";
        break;
    case 32767:
        if(old_xPos == 0)
        {
            qDebug()<<"Joy_MoveLeftStop";
        }
        else
        {
            qDebug()<<"Joy_MoveRightStop";
        }
        break;
    case 65535:
        qDebug()<<"Joy_MoveRight";
        break;
    }
    old_xPos = xPos;
}

void Dialog::AxisY_StateMachine(int yPos)
{
    if(yPos == old_yPos) return;
    switch(yPos)
    {
    case 0:
        qDebug()<<"Joy_MoveForward";
        break;
    case 32767:
        if(old_xPos == 0)
        {
            qDebug()<<"Joy_MoveForwardStop";
        }
        else
        {
            qDebug()<<"Joy_MoveBackwardStop";
        }
        break;
    case 65535:
        qDebug()<<"Joy_MoveBackward";
        break;
    }
    old_yPos = yPos;
}

void Dialog::joyMove(){ // Joystick button action or
    joystick_flag = 0;
#if 0
    send_mutex.lock();
    send_arr[4] = 0x00;
    send_arr[5] = 0x00;
    send_arr[6] = 0x00;
    send_arr[7] = (32767&0xff);
    send_arr[8] = ((32767>>7)&0xff);
    send_arr[9] = (32767&0xff);
    send_arr[10] = ((32767>>7)&0xff);
    send_arr[11] = 0;
    send_arr[12] = 0;
    send_arr[13] = (65535&0xff);
    send_arr[14] = (65535&0xff);
    send_mutex.unlock();
#endif
    JOYINFOEX joyInfoEx;
    joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX));
    joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS;

    qJoyGetPosEx(JOYSTICKID1, &joyInfoEx);//获取游戏设备的坐标位置以及按钮状态

    tableWidget_joys->item(0,1)->setText(QString("%1").arg(joyInfoEx.dwSize));
    tableWidget_joys->item(1,1)->setText(QString("%1").arg(joyInfoEx.dwFlags));
    tableWidget_joys->item(2,1)->setText(QString("%1").arg(joyInfoEx.dwXpos));
    tableWidget_joys->item(3,1)->setText(QString("%1").arg(joyInfoEx.dwYpos));
    tableWidget_joys->item(4,1)->setText(QString("%1").arg(joyInfoEx.dwZpos));
    tableWidget_joys->item(5,1)->setText(QString("%1").arg(joyInfoEx.dwRpos));
    tableWidget_joys->item(6,1)->setText(QString("%1").arg(joyInfoEx.dwUpos));
    tableWidget_joys->item(7,1)->setText(QString("%1").arg(joyInfoEx.dwVpos));
    tableWidget_joys->item(8,1)->setText(QString("%1").arg(joyInfoEx.dwButtons));
    tableWidget_joys->item(9,1)->setText(QString("%1").arg(joyInfoEx.dwButtonNumber));
    tableWidget_joys->item(10,1)->setText(QString("%1").arg(joyInfoEx.dwPOV));
    tableWidget_joys->item(11,1)->setText(QString("%1").arg(joyInfoEx.dwReserved1));
    tableWidget_joys->item(12,1)->setText(QString("%1").arg(joyInfoEx.dwReserved2));

    if(this->mode() == Dialog::SWITCH_MODE)
    {
        AxisX_StateMachine(joyInfoEx.dwXpos);
        AxisY_StateMachine(joyInfoEx.dwYpos);
    }
    else
    {
        Coordinate_StateMachine(joyInfoEx.dwXpos, joyInfoEx.dwYpos);
        Coordinate_zStateMachine(joyInfoEx.dwZpos);
    }
    Button_StateMachine(joyInfoEx.dwButtons);
    POV_StateMachine_Axis(joyInfoEx.dwPOV);

    if(joystick_flag)
    {
        send_mutex.lock();
        send_arr[3] = 0x32;
        send_arr[4] = 0x00;
        send_arr[5] = 0x00;
        send_oneframe(16);
        send_mutex.unlock();
    }

    //QString str;
    unsigned short pos = (unsigned short)joyInfoEx.dwXpos;
    if(joyXPos != pos)
    {
        joyXPos = pos;
        joyX = calcPos(joyXPos);
    }

    pos = (unsigned short)joyInfoEx.dwYpos;
    if(joyYPos != pos)
    {
        joyYPos = pos;
        joyY = calcPos(joyYPos);
    }

    pos = (unsigned int)joyInfoEx.dwZpos;
    if(joyZPos != pos)
    {
        joyZPos = pos;
        joyZ = calcPos(joyZPos);
    }
    //show_str.append("\nZ=" + QString::number(joyInfoEx.dwZpos, 'f', 0));
    pos = (unsigned int)joyInfoEx.dwRpos;
    if(joyRPos != pos)
    {
        joyRPos = pos;
        joyR = calcPos(joyRPos);
    }
    //show_str.append("\nR=" + QString::number(joyInfoEx.dwRpos, 'f', 0));
    if(hasU){
        pos = (unsigned int)joyInfoEx.dwUpos;
        if(joyUPos != pos)
        {
            joyUPos = pos;
            joyU = calcPos(joyUPos);
        }
        //show_str.append("\nU=" + QString::number(joyInfoEx.dwUpos, 'f', 0));
    }

// V programming has problem
    if(hasV){
        pos = (unsigned int)joyInfoEx.dwVpos;
        if(joyVPos != pos)
        {
            joyVPos = pos;
            joyV = calcPos(joyVPos);
        }
        //show_str.append("\nV=" + QString::number(joyInfoEx.dwVpos, 'f', 0) );
    }
}

int Dialog::calcPos(unsigned int joyPos){
    double x = 0;
    x = ((double)joyPos - POS_CENTER)*100 / (POS_MAX - POS_MIN);
    return (int)x;
}







