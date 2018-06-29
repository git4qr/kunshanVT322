#include "dialog.h"
#include "ui_dialog.h"
#include "QDebug"
#include "QDialogButtonBox"
#include "QVBoxLayout"
#include<QSerialPortInfo>
#include <QMessageBox>
//#include<QMutex>
#include <QFormLayout>

QByteArray copy_bytearray;
volatile unsigned char rcv_buf[5000];
volatile unsigned int BufWrite = 0;
volatile unsigned int BufRead = 0;
volatile unsigned char BufRcvStatus=BUFFER_EMPTY;
volatile qint32 recvNum =0;

QByteArray socket_copy_bytearray;
volatile qint32 socket_recvNum =0;
volatile unsigned char socket_rcv_buf[5000];
volatile unsigned int socket_BufWrite = 0;
volatile unsigned int socket_BufRead = 0;
volatile unsigned char socket_BufRcvStatus=BUFFER_EMPTY;

int connect_flag = 0;


QString ShowHex(QByteArray str)
{
    QDataStream out(&str,QIODevice::ReadWrite);   //将字节数组与数据流关联，操作数据流等同于操作字节数组；
    QString buf;

    while(!out.atEnd())  // 判断是否已经到数据末端
    {
        quint8 outChar = 0;
        out >> outChar;             //每次一个字节的拷贝至 outchar
        QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0')).trimmed().toUpper() + QString(" ");   //2 字符宽度
        buf += str;
    }
    return buf;
}

void Dialog::parse_bytearray()
{
     QDataStream out(copy_bytearray);
    int add_cnt = 0;
    unsigned char tmp_buf[1000];
    while(!out.atEnd()) {
        quint8 outChar = 0;
        out >> outChar;
         tmp_buf[add_cnt++] = outChar;
    }
    for(int i = 0; i<add_cnt; i++)
    {
        rcv_buf[ BufWrite++ ] = tmp_buf[i];

        BufWrite %= sizeof(rcv_buf);

        if (BufWrite == BufRead) {
            BufRcvStatus = BUFFER_FULL;
        }
        else {
            BufRcvStatus = BUFFER_DATA;
         }
    }
}

void Dialog::RcvData_SerialPort()
{
    RcvData = serialPort_command->readAll();
    copy_bytearray = RcvData;
    emit copy_Done();
    QString rcvBuf;
    recvNum += RcvData.length();
    ui->label_recv_bytes->setNum(recvNum);

    rcvBuf = ShowHex(RcvData);
    ui->textEdit_ShowRcvData->setTextColor(QColor(Qt::blue));
    ui->textEdit_ShowRcvData->append(rcvBuf);
    RcvData.clear();
}

QStringList AvailablePorts()
{
    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
       list << info.portName();
    }
    if (list.empty() == true) {
        list << "Com1";
    }
    return list;
}

qint32 mySetSerialBaud( QSerialPort *com, QComboBox *combobox)
{
    qint32 num = combobox->currentText().toInt();

    switch(num)
    {   // 此处的Baud1200--Baud115200，是QSerialPort类中的枚举量
        case QSerialPort::Baud1200:
        com->setBaudRate(QSerialPort::Baud1200);
        break;
        case QSerialPort::Baud2400:
        com->setBaudRate(QSerialPort::Baud2400);
        break;
        case QSerialPort::Baud4800:
        com->setBaudRate(QSerialPort::Baud4800);
        break;
        case QSerialPort::Baud9600:
        com->setBaudRate(QSerialPort::Baud9600);
        break;
        case QSerialPort::Baud19200:
        com->setBaudRate(QSerialPort::Baud19200);
        break;
        case QSerialPort::Baud38400:
        com->setBaudRate(QSerialPort::Baud38400);
        break;
        case QSerialPort::Baud57600:
        com->setBaudRate(QSerialPort::Baud57600);
        break;
        case QSerialPort::Baud115200:
        com->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        break;
    }
    return num;
}

QSerialPort::DataBits mySetSerialDataBits( QSerialPort *com,QComboBox *combobox)
{
    QSerialPort::DataBits num = (QSerialPort::DataBits)combobox->currentText().toInt();
    switch(num)
    {   // 此处的Data5\6\7\8，是QSerialPort类中的枚举量
        case QSerialPort::Data5:
        com->setDataBits(QSerialPort::Data5);
        break;
        case QSerialPort::Data6:
        com->setDataBits(QSerialPort::Data6);
        break;
        case QSerialPort::Data7:
        com->setDataBits(QSerialPort::Data7);
        break;
        case QSerialPort::Data8:
        com->setDataBits(QSerialPort::Data8);
        break;
        default:
        break;
    }
    return num;
}

QSerialPort::Parity mySetSerialParity(QSerialPort *com,QComboBox *combobox)
{
    QSerialPort::Parity num =(QSerialPort::Parity)combobox->currentIndex();


    switch(num)
    {   // 此处的 0,1,2代表的是下拉框的索引值；
        case 0:
        com->setParity(QSerialPort::EvenParity);
        break;
        case 1:
        com->setParity(QSerialPort::NoParity);
        break;
        case 2:
        com->setParity(QSerialPort::OddParity);
        break;

        default:
        break;
    }

    return num;
}

QSerialPort::StopBits smySetSerialStopBit(QSerialPort *com,QComboBox *combobox)
{
    QSerialPort::StopBits num = (QSerialPort::StopBits)combobox->currentIndex();
    switch(num)
    {   // 此处的 0,1,2代表的是下拉框的索引值；
        case 0:
        com->setStopBits(QSerialPort::OneStop);
        break;
        case 1:
        com->setStopBits(QSerialPort::OneAndHalfStop);
        break;
        case 2:
        com->setStopBits(QSerialPort::TwoStop);
        break;
        default:
        break;
    }
    return num;
}

void Dialog::onMsg()
{
    static int init = 0;
    QString name,name_new;
    /*if(init == 0)
    {
        init =1;
        name="";
    }
    else
    */
        name = box->currentText();

    if ( dialog.exec() == QDialog::Accepted)
    {
        name_new = box->currentText();
        //if(name.compare(name_new) != 0)
        //{
            serialPort_command->close();
            serialPort_command->setPortName(name_new);
            bool openflag = serialPort_command->open(QIODevice::ReadWrite);
            if(true == openflag ) {
                connect_flag = 1;
                mySetSerialBaud(serialPort_command,box3);
                mySetSerialDataBits(serialPort_command,box5);
                mySetSerialParity(serialPort_command,box4);
                smySetSerialStopBit(serialPort_command,box6);
                connect(serialPort_command, &QSerialPort::readyRead, this, &Dialog::RcvData_SerialPort);//当有数据来时，触发接收槽函数；
            }
            else  {// 串口打开失败时，弹出提示窗口
                QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
            }
        //}
        /*else
        {
            mySetSerialBaud(serialPort_command,box3);
            mySetSerialDataBits(serialPort_command,box5);
            mySetSerialParity(serialPort_command,box4);
            smySetSerialStopBit(serialPort_command,box6);
        }*/
    }
}

void Dialog::onMsgC()
{
    if ( dialog_socket.exec() == QDialog::Accepted)
    {
        int port;
        QString IP;
        port = lineEdit3_c3->text().toInt();
        IP = lineEdit4_c3->text();

        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(30000))
        {
            qDebug() << "Connection failed!";
            QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
            return;
        }
        qDebug() << "Connect successfully!";
        connect_flag = 2;

    }
}

void Dialog::init_dialog_sys()
{
    dialog.setWindowTitle(tr("串口配置"));
    QStringList list = AvailablePorts();

    groupBox_trackboard = new QGroupBox();
    groupBox_trackboard->setTitle("跟踪板");
    box = new QComboBox(groupBox_trackboard);
    box->addItems(list);
    //box2 = new QComboBox(groupBox_trackboard);
    //box2->addItems(list);
    box3 = new QComboBox(groupBox_trackboard);
    box3->addItem("115200");
    box3->addItem("1200");
    box3->addItem("2400");
    box3->addItem("4800");
    box3->addItem("9600");
    box3->addItem("19200");
    box3->addItem("38400");
    box3->addItem("57600");
    box4 = new QComboBox(groupBox_trackboard);
    box4->addItem("Even");
    box4->addItem("None");
    box4->addItem("Odd");
    box5 = new QComboBox(groupBox_trackboard);
    box5->addItem("8");
    box5->addItem("7");
    box5->addItem("6");
    box5->addItem("5");
    box6 = new QComboBox(groupBox_trackboard);
    box6->addItem("1");
    box6->addItem("1.5");
    box6->addItem("2");
//-------------------------
#if 0
    groupBox_hspeed = new QGroupBox(&dialog);
    groupBox_hspeed->setTitle("高速球");
    checkBox = new QCheckBox(groupBox_hspeed);
    checkBox->setText("使能");
    box7 = new QComboBox(groupBox_hspeed);
    box7->addItems(list);
    box8 = new QComboBox(groupBox_hspeed);
    box8->addItem("1200");
    box8->addItem("2400");
    box8->addItem("4800");
    box8->addItem("9600");
    box8->addItem("19200");
    box8->addItem("38400");
    box8->addItem("57600");
    box8->addItem("115200");
    box9 = new QComboBox(groupBox_hspeed);
    box9->addItem("None");
    box9->addItem("Odd");
    box9->addItem("Even");
    box10 = new QComboBox(groupBox_hspeed);
    box10->addItem("8");
    box10->addItem("7");
    box10->addItem("6");
    box10->addItem("5");
    box11 = new QComboBox(groupBox_hspeed);
    box11->addItem("1");
    box11->addItem("1.5");
    box11->addItem("2");
#endif
//-------------------------
    button = new QDialogButtonBox(&dialog);
    button->addButton( "OK", QDialogButtonBox::YesRole);
    button->addButton( "Cancel", QDialogButtonBox::NoRole);
    connect(button, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(button, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QFormLayout *playout_s1 = new QFormLayout();
    playout_s1->addRow(QStringLiteral("命令端口"), box);
    //playout_s1->addRow(QStringLiteral("日志端口"), box2);
    playout_s1->addRow(QStringLiteral("波特率"), box3);
    playout_s1->addRow(QStringLiteral("校验"), box4);
    playout_s1->addRow(QStringLiteral("数据位"), box5);
    playout_s1->addRow(QStringLiteral("停止位"), box6);
    groupBox_trackboard->setLayout(playout_s1);
#if 0
    QFormLayout *playout_s2 = new QFormLayout;
    playout_s2->addRow(QStringLiteral("端口"), box7);
    playout_s2->addRow(QStringLiteral("波特率"), box8);
    playout_s2->addRow(QStringLiteral("校验"), box9);
    playout_s2->addRow(QStringLiteral("数据位"), box10);
    playout_s2->addRow(QStringLiteral("停止位"), box11);
    QVBoxLayout *mainlayout2 = new QVBoxLayout;
    mainlayout2->addWidget(checkBox);
    mainlayout2->addLayout(playout_s2);
    groupBox_hspeed->setLayout(mainlayout2);
#endif
//----
    QHBoxLayout *mainlayout3 = new QHBoxLayout;
    mainlayout3->addWidget(groupBox_trackboard);
    //mainlayout3->addWidget(groupBox_hspeed);

    QVBoxLayout *mainlayout4 = new QVBoxLayout;
    mainlayout4->addLayout(mainlayout3);
    mainlayout4->addWidget(button);

    dialog.setLayout(mainlayout4);

//===============
    dialog_socket.setWindowTitle(tr("网络配置"));
    lineEdit3_c3 = new QLineEdit();
    lineEdit4_c3 = new QLineEdit();
    button_socket = new QDialogButtonBox(&dialog_socket);
    button_socket->addButton( "OK", QDialogButtonBox::YesRole);
    button_socket->addButton( "Cancel", QDialogButtonBox::NoRole);
    connect(button_socket, SIGNAL(accepted()), &dialog_socket, SLOT(accept()));
    connect(button_socket, SIGNAL(rejected()), &dialog_socket, SLOT(reject()));
    QFormLayout *pLayout_socket = new QFormLayout();
    pLayout_socket->addRow(QStringLiteral("IP："), lineEdit4_c3);
    pLayout_socket->addRow(QStringLiteral("端口："), lineEdit3_c3);
    QVBoxLayout *socket_layout2 = new QVBoxLayout;
    socket_layout2->addLayout(pLayout_socket);
    socket_layout2->addWidget(button_socket);
    dialog_socket.setLayout(socket_layout2);
}

char convertHex2Char(char ch)
{
    if((ch >= '0') && (ch <= '9'))
    {
        return ch-0x30;
    }
    else if((ch >= 'A') && (ch <= 'F'))
    {
        return ch - 'A' + 10;
    }

    else if((ch >= 'a') && (ch <= 'f'))
    {
        return ch - 'a' + 10;
    }
    else
    {
        return (-1);
    }

}

QByteArray Dialog::string2hex(QString str,bool &flag)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    char lstr,hstr;

    senddata.resize(len/2);

    for(int i=0; i<len; i++)
    {
        hstr = str[i].toLatin1();
        if(hstr == ' ')
        {
            continue;
        }
        i++;
        lstr = str[i].toLatin1();
        if(lstr == ' ' || i >= len)
        {
            hexdata = 0;
            lowhexdata = convertHex2Char(hstr);
          }
        else
        {
            hexdata = convertHex2Char(hstr);
            lowhexdata = convertHex2Char(lstr);
        }

        if( (hexdata == -1) || (lowhexdata == -1) )
        {
            flag = false;
            senddata.resize(hexdatalen);
            return senddata;
        }
        else
        {
            hexdata = hexdata * 16 + lowhexdata;
        }

        senddata[hexdatalen] = (char) hexdata;
        hexdatalen ++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
void Dialog::socket_Read_Data()
{
    /*QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer);
        //刷新显示
        ui->textEdit_Recv->setText(str);
    }*/

    socketRcvData = socket->readAll();//读网口
    socket_copy_bytearray = socketRcvData;
    emit socket_copy_Done();
    QString rcvBuf;
    socket_recvNum += socketRcvData.length();
    ui->label_recv_bytes->setNum(socket_recvNum);

    rcvBuf = ShowHex(socketRcvData);

    ui->textEdit_ShowRcvData->setTextColor(QColor(Qt::blue));
    ui->textEdit_ShowRcvData->append(rcvBuf);
    socketRcvData.clear();
}
void Dialog::socket_parse_bytearray()
{
     QDataStream out(socket_copy_bytearray);
    int add_cnt = 0;
    unsigned char tmp_buf[1000];
    while(!out.atEnd()) {
        quint8 outChar = 0;
        out >> outChar;
         tmp_buf[add_cnt++] = outChar;
    }
    for(int i = 0; i<add_cnt; i++)
    {
        socket_rcv_buf[ socket_BufWrite++ ] = tmp_buf[i];

        socket_BufWrite %= sizeof(socket_rcv_buf);

        if (socket_BufWrite == socket_BufRead) {
            socket_BufRcvStatus = BUFFER_FULL;
        }
        else {
            socket_BufRcvStatus = BUFFER_DATA;
         }
    }
}
