#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QMenuBar"
#include<QSerialPort>
#include "ui_dialog.h"
#include "QDialogButtonBox"
#include <QBoxLayout>
#include <QListWidget>
#include <recvserial.h>
#include <recvsocket.h>
#include <QTcpSocket>
#include<QMutex>

#include<QString>
#include<QStringList>
#include<QDebug>
#include<QDataStream>
#include<QSerialPortInfo>
#include<QTime>
#include<QTimer>
#include<QByteArray>
#include <QMainWindow>
#include <QEvent>

#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767
#define POINTX 610 //矩形中心点坐标X
#define POINTY 93 //矩形中心点坐标Y
#define WIDTH 1920
#define HEIGHT 1080
#define RATIO 10 //矩形框缩小比例

#define BUFFER_FULL          1
#define BUFFER_DATA          2
#define BUFFER_EMPTY         3

extern QMutex send_mutex;
extern unsigned char send_arr[64];

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    enum MODE{SWITCH_MODE, COORDINATE_MODE};
    explicit Dialog(enum MODE mode = COORDINATE_MODE,QWidget *parent = 0);
    enum MODE mode() const {return m_mode;}
    ~Dialog();
    void RcvData_SerialPort();
    void parse_bytearray();
    void init_dialog_sys();
    void init_dialog_joys();
    void init_menu();
    void init_dialog_c1();
    void init_dialog_c2();
    void init_dialog_c3();
    void init_dialog_c4();
    void init_table();
    void init_table_Profile();
    void init_table_camera_Profile();
    void load_profile();
    void load_camera_profile();
    QMenuBar* menuBar;
    QMenu* menu[10];
    QAction* act[10];
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent ( QMouseEvent * e );
    void mouseMoveEvent(QMouseEvent *event);
    void send_oneframe(int length);
    QByteArray string2hex(QString str,bool &flag);
    volatile qint32 sendNum =0;
    void stop_thread_now();
    void output_to_label(int i);
    void socket_parse_bytearray();
    void check_iftimeout();

    /************************/
    void init_dialog();//用于配置所有的dialog
    void init_dialog_config();//配置平台参数
    void init_dialog_PID();//配置PID
    void init_dialog_JosHandle();//配置手柄控制
    void init_dialog_JosMap1();//手柄按键映射1
    void init_dialog_JosMap2();//手柄按键映射2
    void init_dialog_KeyboardMap1();//键盘按键映射1
    void init_dialog_KeyboardMap2();//键盘按键映射2
    void init_dialog_SerialParam();//串口参数配置
    void init_dialog_UTCParam1();//UTC参数配置1
    void init_dialog_UTCParam2();//UTC参数配置2
    void init_dialog_UTCParam3();//UTC参数配置3
    void init_dialog_EMParam();//增强和多目标算法配置
    void init_dialog_OSDParam1();//OSD参数配置1
    void init_dialog_OSDParam2();//OSD参数配置2
    void init_dialog_OSDParam3();//OSD参数配置3
    void init_dialog_CameraParam1();//相机参数1
    void init_dialog_CameraParam2();//相机参数2
    void init_dialog_CameraParam3();
    void init_dialog_CameraParam4();
    void init_dialog_CameraParam5();
    void init_dialog_CameraParam6();
    void init_dialog_CameraParam7();
    void init_dialog_CameraParam8();
    void init_dialog_CameraParam9();
    void init_dialog_CameraParam10();
    void init_dialog_CameraParam11();
    void init_dialog_CameraParam12();
    void init_dialog_CameraParam13();
    void init_dialog_CameraParam14();
    void init_dialog_CameraParam15();
    void init_dialog_CameraParam16();
    void init_dialog_CameraParam17();
    void init_dialog_CameraParam18();
    void init_dialog_CameraParam19();
    void init_dialog_CameraParam20();
    void init_dialog_CameraParam21();
    void init_dialog_CameraParam22();
    void init_dialog_CameraParam23();
    void init_dialog_CameraParam24();
    void init_dialog_CameraParam25();
    void init_dialog_CameraParam26();
    void init_dialog_CameraParam27();




private slots:
    void on_pushButton_model_clicked();
    void on_pushButton_normal_clicked();
    void on_pushButton_mixed_clicked();
    void onMsg();
    void onMsgB();
    void onMsgC();
    void onMsgD();
    void onMsgE();
    void onMsgF();
    void onMsgG();
    void onMsgsc();
    void onMesgp();
    void on_pushButton_send_clicked();
    void doubleclick(QListWidgetItem *item);
    void on_pushButton_lastpage_clicked();
    void on_checkBox_autocheck_stateChanged(int arg1);
    void on_comboBox_channel_activated(int index);
    void on_comboBox_channelbind_activated(int index);
    void on_pushButton_trk_clicked();
    void on_comboBox_zoom_activated(int index);
    void on_comboBox_mmtselect_activated(int index);
    void on_pushButton_mmt_clicked();
    void on_pushButton_mtd_clicked();
    void on_pushButton_enh_clicked();
    void on_pushButton_pinp_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_lu_clicked();
    void on_pushButton_ld_clicked();
    void on_pushButton_ru_clicked();
    void on_pushButton_rd_clicked();
    void on_pushButton_axissave_clicked();
    void on_comboBox_color_activated(int index);
    void on_comboBox_font_activated(int index);
    void on_comboBox_fontsize_activated(int index);
    void on_comboBox_osddisplay_activated(int index);
    void on_comboBox_optzoom_activated(int index);
    void on_comboBox_aperture_activated(int index);
    void on_comboBox_focal_activated(int index);
    void on_comboBox_videochannel_activated(int index);
    void on_comboBox_frc_activated(int index);
    void on_comboBox_videoq_activated(int index);
    void on_comboBox_vqc_activated(int index);
    void on_comboBox_keystatus_activated(int index);
    void on_comboBox_sectrk_activated(int index);
    void socket_Read_Data();
    void on_lineEdit_jiaoju_editingFinished();
    void on_pushButton_setconf_clicked();
    void on_pushButton_getconf_clicked();

    int openJoy();
    void closeJoy();
    void Button_StateMachine(int button);//new
    void Coordinate_StateMachine(int xPos, int yPos);
    void Coordinate_zStateMachine(int zPos);
    void AxisY_StateMachine(int yPos);
    void AxisX_StateMachine(int xPos);
    void POV_StateMachine_Axis(int pov);
    void joyMove();
    int calcPos(unsigned int);
    void on_J1_pressed();
    /*void on_J2_clicked();
    void on_J3_clicked();
    void on_J4_clicked();
    void on_J5_clicked();
    void on_J6_clicked();
    void on_J7_clicked();
    void on_J8_clicked();
    void on_J9_clicked();
    void on_J10_clicked();
    void on_J11_clicked();
    void on_J12_clicked();*/
    void on_J1_released();

    /***********用于接收Programmer信号的槽函数******************/
    void receivePlatConfig();
    void receivePID();
    void receiveJoshandle();
    void receiveJosMap1();
    void receiceJosMap2();
    void receiceKeyboardMap1();
    void receiveKeyboardMap2();
    void receiveUTC1();
    void receiveUTC2();
    void receiveUTC3();
    void receiveSerial();
    void receiveEM();
    void receiveOSD1();
    void receiveOSD2();
    void receiveOSD3();
    void receiveCamera1();
    void receiveCamera2();
    void receiveCamera3();
    void receiveCamera4();
    void receiveCamera5();
    void receiveCamera6();
    void receiveCamera7();
    void receiveCamera8();
    void receiveCamera9();
    void receiveCamera10();
    void receiveCamera11();
    void receiveCamera12();
    void receiveCamera13();
    void receiveCamera14();
    void receiveCamera15();
    void receiveCamera16();
    void receiveCamera17();
    void receiveCamera18();
    void receiveCamera19();
    void receiveCamera20();
    void receiveCamera21();
    void receiveCamera22();
    void receiveCamera23();
    void receiveCamera24();
    void receiveCamera25();
    void receiveCamera26();
    void receiveCamera27();

/******************配置文件用于发送的槽函数*****************************/
    void on_tableWidget_Profile_itemChanged(QTableWidgetItem *item);
    void on_tableWidget_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabwidget_pid_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabwidget_pid_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_JosHandle_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_JosHandle_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_Josmap1_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_Josmap1_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_Josmap2_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_Josmap2_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_Keyboardmap1_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_Keyboardmap1_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_Keyboardmap2_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_Keyboardmap2_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_SerialParam_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_SerialParam_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_UTCParam1_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_UTCParam1_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_UTCParam3_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_UTCParam3_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_UTCParam2_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_UTCParam2_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_EMParam_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_EMParam_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_OSDParam1_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_OSDParam1_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_OSDParam2_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_OSDParam2_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_OSDParam3_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_OSDParam3_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam1_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam1_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam2_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam2_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam3_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam3_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam4_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam4_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam5_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam5_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam6_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam6_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam7_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam7_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam8_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam8_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam9_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam9_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam10_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam10_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam11_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam11_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam12_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam12_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam13_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam13_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam14_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam14_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam15_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam15_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam16_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam16_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam17_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam17_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam18_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam18_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam19_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam19_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam20_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam20_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam21_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam21_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam22_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam22_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam23_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam23_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam24_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam24_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam25_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam25_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam26_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam26_camera_Profile_itemActivated(QTableWidgetItem *item);

    void on_tabWidget_CameraParam27_camera_Profile_itemChanged(QTableWidgetItem *item);
    void on_tabWidget_CameraParam27_camera_Profile_itemActivated(QTableWidgetItem *item);

private:

    Ui::Dialog *ui;
    QSerialPort * serialPort_command;
    QByteArray  RcvData;
    QDialog  dialog;
    QComboBox *box,*box1,*box2,*box3,*box4,*box5,*box6,*box7,*box8,*box9,*box10,*box11;
    QGroupBox *groupBox_trackboard,*groupBox_hspeed;
    QDialogButtonBox *button;
    QCheckBox *checkBox;
    QByteArray sndData_02;
//-----
    QDialog dialog_config,dialog_c1,dialog_c2,dialog_c3,dialog_c4;
    QListWidget *listWidget;
    QDialogButtonBox *button_config;
    QPushButton *upd_c1,*def_c1;
    QLabel *labelt_c1;
    QComboBox *box1_c1,*box2_c1,*box5_c1;
    QCheckBox *checkBox3_c1;
    QLineEdit *lineEdit4_c1,*lineEdit6_c1,*lineEdit7_c1,*lineEdit8_c1,*lineEdit9_c1,*lineEdit10_c1;

    QPushButton *upd_c2,*def_c2;
    QLabel *labelt_c2;
    QComboBox *box1_c2,*box2_c2,*box3_c2,*box4_c2,*box14_c2;
    QLineEdit *lineEdit5_c2,*lineEdit6_c2,*lineEdit7_c2,*lineEdit8_c2,*lineEdit9_c2,*lineEdit10_c2,*lineEdit11_c2;
    QCheckBox *checkBox12_c2,*checkBox13_c2;

    RcvSerialdata *thread_01;
//-----
    QDialog dialog_socket;
    QLabel *label1_c3,*label2_c3;
    QLineEdit *lineEdit3_c3,*lineEdit4_c3;
    QDialogButtonBox *button_socket;

    QTcpSocket *socket;
    QByteArray  socketRcvData;
    RcvSocketdata *thread_socket;
    QTimer *send_timer;
    int timeval_select;
    int load_config_flag;

    //-----
    QDialog dialog_joys;
    QTableWidget *tableWidget_joys;
    QPushButton *openjoys, *closejoys;
    QSlider *horizontalSlider;
    QPushButton *POVU,*POVUR,*POVR,*POVDR,*POVD,*POVDL,*POVL,*POVUL,*POVCEN;
    QPushButton *J1,*J2,*J3,*J4,*J5,*J6,*J7,*J8,*J9,*J10,*J11,*J12;

    int m_button[16];//new
    int old_xPos;
    int old_yPos;
    int old_zPos;
    int old_pov;
    bool pov_forward;
    bool pov_backward;
    bool pov_left;
    bool pov_right;
    bool pov_center;
    enum MODE m_mode;
    int a, b, m_dragging;
    unsigned short sqmax;
    unsigned short sqmin;

    QTimer *timer;
    unsigned int joyXPos, joyYPos, joyZPos, joyRPos, joyUPos, joyVPos, period;
    int numButtons, numAxes;
    int joyX, joyY, joyZ, joyR, joyU, joyV;
    bool hasU, hasV;

    /**********************************/
    QMenu *menuc;
    //------------
     QDialog  dialog_pid, dialog_JosHandle, dialog_Josmap1,dialog_Josmap2,
             dialog_Keyboardmap1, dialog_Keyboardmap2, dialog_SerialParam, dialog_UTCParam1,
             dialog_UTCParam2, dialog_UTCParam3, dialog_EMParam, dialog_OSDParam1,
             dialog_OSDParam2, dialog_OSDParam3, dialog_CameraParam1, dialog_CameraParam2,
             dialog_CameraParam3, dialog_CameraParam4, dialog_CameraParam5, dialog_CameraParam6,
             dialog_CameraParam7, dialog_CameraParam8, dialog_CameraParam9,
             dialog_CameraParam10, dialog_CameraParam11, dialog_CameraParam12, dialog_CameraParam13,
             dialog_CameraParam14, dialog_CameraParam15, dialog_CameraParam16, dialog_CameraParam17,
             dialog_CameraParam18, dialog_CameraParam19, dialog_CameraParam20, dialog_CameraParam21,
             dialog_CameraParam22, dialog_CameraParam23, dialog_CameraParam24, dialog_CameraParam25,
             dialog_CameraParam26, dialog_CameraParam27;
    //------------
     QTabWidget *tabWidget, *tabwidget_pid, *tabWidget_JosHandle, *tabWidget_Josmap1,*tabWidget_Josmap2,
                *tabWidget_Keyboardmap1, *tabWidget_Keyboardmap2, *tabWidget_SerialParam, *tabWidget_UTCParam1,
                *tabWidget_UTCParam2, *tabWidget_UTCParam3, *tabWidget_EMParam, *tabWidget_OSDParam1,
                *tabWidget_OSDParam2, *tabWidget_OSDParam3, *tabWidget_CameraParam1, *tabWidget_CameraParam2,
                *tabWidget_CameraParam3, *tabWidget_CameraParam4, *tabWidget_CameraParam5, *tabWidget_CameraParam6,
                *tabWidget_CameraParam7, *tabWidget_CameraParam8, *tabWidget_CameraParam9,
                *tabWidget_CameraParam10, *tabWidget_CameraParam11, *tabWidget_CameraParam12, *tabWidget_CameraParam13,
                *tabWidget_CameraParam14, *tabWidget_CameraParam15, *tabWidget_CameraParam16, *tabWidget_CameraParam17,
                *tabWidget_CameraParam18, *tabWidget_CameraParam19, *tabWidget_CameraParam20, *tabWidget_CameraParam21,
                *tabWidget_CameraParam22, *tabWidget_CameraParam23, *tabWidget_CameraParam24, *tabWidget_CameraParam25,
                *tabWidget_CameraParam26, *tabWidget_CameraParam27;
     QTableWidget *tableWidget_Profile,*tabwidget_pid_Profile, *tabWidget_JosHandle_Profile, *tabWidget_Josmap1_Profile,*tabWidget_Josmap2_Profile,
                    *tabWidget_Keyboardmap1_Profile, *tabWidget_Keyboardmap2_Profile, *tabWidget_SerialParam_Profile, *tabWidget_UTCParam1_Profile,
                    *tabWidget_UTCParam2_Profile, *tabWidget_UTCParam3_Profile, *tabWidget_EMParam_Profile, *tabWidget_OSDParam1_Profile,
                    *tabWidget_OSDParam2_Profile, *tabWidget_OSDParam3_Profile;
     QTableWidget *tabWidget_CameraParam1_camera_Profile, *tabWidget_CameraParam2_camera_Profile,
                     *tabWidget_CameraParam3_camera_Profile, *tabWidget_CameraParam4_camera_Profile, *tabWidget_CameraParam5_camera_Profile, *tabWidget_CameraParam6_camera_Profile,
                     *tabWidget_CameraParam7_camera_Profile, *tabWidget_CameraParam8_camera_Profile, *tabWidget_CameraParam9_camera_Profile,
                     *tabWidget_CameraParam10_camera_Profile, *tabWidget_CameraParam11_camera_Profile, *tabWidget_CameraParam12_camera_Profile, *tabWidget_CameraParam13_camera_Profile,
                     *tabWidget_CameraParam14_camera_Profile, *tabWidget_CameraParam15_camera_Profile, *tabWidget_CameraParam16_camera_Profile, *tabWidget_CameraParam17_camera_Profile,
                     *tabWidget_CameraParam18_camera_Profile, *tabWidget_CameraParam19_camera_Profile, *tabWidget_CameraParam20_camera_Profile, *tabWidget_CameraParam21_camera_Profile,
                     *tabWidget_CameraParam22_camera_Profile, *tabWidget_CameraParam23_camera_Profile, *tabWidget_CameraParam24_camera_Profile, *tabWidget_CameraParam25_camera_Profile,
                     *tabWidget_CameraParam26_camera_Profile, *tabWidget_CameraParam27_camera_Profile;

/*****************************配置文件 中文名显示************************************************/
     QString string_config[16]={"0","Platform output method","scalarX","scalarY","demandMaxX","demandMinX","demandMaxY","demandMinY","deadbandX","deadbandY","driftX","driftY","bleedUsed","bleedX","bleedY","0"},
             string_pid[16]={"0","P0","P1","P2","I1","I2","G","P0","P1","P2","I1","I2","G","0","0","0"},
             string_JosHandle[16]={"0","fCutpointX","fCutpointY","fInputGain_X","fInputGain_Y","fDeadband","fPlatformAcquisitionModeGain_X","fPlatformAcquisitionModeGain_Y","0","0","0","0","0","0","0","0"},
            string_JosMap1[16]={"0","jos_1","jos_2","jos_3","jos_4","jos_5","jos_6","jos_7","jos_8","jos_9","jos_10","jos_11","jos_12","0","0","0"},
            string_JosMap2[16]={"jos_axle1_x","jos_axle1_y","jos_axle2_x","jos_axle2_y","jos_axle3_x","jos_axle3_y","0","0","0","0","0","0","0","0","0","0"},
            string_Key1[16]={"0","0","key_a","key_b","key_c","key_d","key_e","key_f","key_g","key_h","key_i","key_j","key_k","key_l","key_m","key_n"},
            string_Key2[16]={"0","key_o","key_p","key_q","key_r","key_s","key_t","key_u","key_v","key_w","key_x","key_y","key_z","0","0","0"},
            string_Serial[16]={"0","UartDev","BaudRate","DataBits","ParityBit","StopBits","FlowCtrl","0","0","0","0","0","0","0","0","0"},
            string_UTC1[16]={"occlusion_thred","retry_acq_thred","up_factor","res_distance","res_area","gapframe","enhEnable","cliplimit","dictEnable","moveX","moveY","moveX2","moveY2","segPixelX","segPixelY","algOsdRectEnable"},
            string_UTC2[16]={"ScalerLarge","ScalerMid","ScalerSmall","Scatter","ratio","FilterEnable","BigSecEnable","SalientThred","ScalerEnable","DynamicRatioEnable","acqSize.width","acqSize.height","TrkAim 4:3 Enable","SceneMVEnable","BlaceTrackEnable","bAveTrkPos"},
            string_UTC3[16]={"fTau","buildFrms","LostFrmThrd","histMvThred","detectFrms","stillFrms","stillThred","bKalmanFilter","xMVThred","yMVThred","xStillThred","yStillThred","slopeThred","kalmanHistThred","kalCoefQ","kaimanCoefR"},
            string_EM[16]={"Enhmod_0","Enhparm","Mntdparm_1","Mntdparm_2","Mntdparm_3","Mntdparm_4","Mntdparm_5","Mntdparm_6","Mntdparm_7","Mntparm_8","utcAcqinterval","0","0","0","0","0"},
            string_OSD1[16]={"MAIN_Sersor","Timedisp_9","OSD_text_show","OSD_text_color","OSD_text_alpha","OSD_text_font","OSD_text_size","OSD_draw_show","OSD_draw_color","CROSS_AXIS_WIDTH","CROSS_AXIS_HEIGHT","Picp_CROSS_AXIS_WIDTH","Picp_CROSS_AXIS_HEIGHT","ch0_acqRect_width","ch1_acqRect_width","ch2_acqRect_width"},
            string_OSD2[16]={"ch3_acqRect_width","ch4_acqRect_width","ch5acqRect_width","ch0_acqRect_height","ch1_acqRect_height","ch2_acqRect_height","ch3_acqRect_height","ch4_acqRect_height","ch5_acqRect_height","ch0_aim_width","ch1_aim_width","ch2_aim_width","ch3_aim_width","ch4_aim_width","ch5_aim_width","ch6_aim_width"},
            string_OSD3[16]={"ch1_aim_height","ch2_aim_height","ch3_aim_height","ch4_aim_height","ch5_aim_height","0","0","0","0","0","0","0","0","0","0"},
            string_C1[16]={"initMode","VIDEO_CHID0_FRAME_RATE","VIDEO_CHID1_FRAME_RATE","VIDEO_CHID2_FRAME_RATE","VIDEO_CHID3_FRAM_RATE","VIDEO_CHID4_FRAM_RATE","VIDEO_CHID5_FRAM_RATE","VIDEO_CHID1_RORMAT","VIDEO_CHID2_FORMAT","VIDEO_CHID3_FORMAT","VIDEO_CHID4_FORMAT","VIDEO_CHID5_FORMAR","FOV_MODE","0","0"},
            string_C2[16]={"CH0_HFOV1","CH0_HOV2","CH0_HOV3","CH0_HOV4","CHO_HOV5","CH0_HOV6","CH0_HOV7","CH0_HOV8","CH0_HOV9","CH0_HOV10","CH0_HOV11","CH0_HOV12","CH0_HOV13","0","0","0"},
            string_C3[16]={"CH1_HFOV1","CH1_HOV2","CH1_HOV3","CH1_HOV4","CH1_HOV5","CH1_HOV6","CH1_HOV7","CH1_HOV8","CH1_HOV9","CH1_HOV10","CH1_HOV11","CH1_HOV12","CH1_HOV13","0","0","0"},
            string_C4[16]={"CH2_HFOV1","CH2_HOV2","CH2_HOV3","CH2_HOV4","CH2_HOV5","CH2_HOV6","CH2_HOV7","CH2_HOV8","CH2_HOV9","CH2_HOV10","CH2_HOV11","CH2_HOV12","CH2_HOV13","0","0","0"},
            string_C5[16]={"CH3_HFOV1","CH3_HOV2","CH3_HOV3","CH3_HOV4","CH3_HOV5","CH3_HOV6","CH3_HOV7","CH3_HOV8","CH3_HOV9","CH3_HOV10","CH3_HOV11","CH3_HOV12","CH3_HOV13","0","0","0"},
            string_C6[16]={"CH4_HFOV1","CH1_HOV2","CH4_HOV3","CH4_HOV4","CH4_HOV5","CH4_HOV6","CH4_HOV7","CH4_HOV8","CH4_HOV9","CH4_HOV10","CH4_HOV11","CH4_HOV12","CH4_HOV13","0","0","0"},
            string_C7[16]={"CH5_HFOV1","CH5_HOV2","CH5_HOV3","CH5_HOV4","CH5_HOV5","CH5_HOV6","CH5_HOV7","CH5_HOV8","CH5_HOV9","CH5_HOV10","CH5_HOV11","CH5_HOV12","CH5_HOV13","0","0","0"},
            string_C8[16]={"CH0_FOV_Ratio","CH1_FOV_Ratio","CH2_FOV_Ratio","CH3_FOV_Ratio","CH4_FOV_Ratio","CH5_FOV_Ratio","0","0","0","0","0","0","0","0","0","0"},
            string_C9[16]={"CH0_FOV1_Boresight_X","CH0_FOV2_Boresight_X","CH0_FOV3_Boresight_X","CH0_FOV4_Boresight_X","CH0_FOV5_Boresight_X","CH0_FOV6_Boresight_X","CH0_FOV7_Boresight_X","CH0_FOV8_Boresight_X","CH0_FOV9_Boresight_X","CH0_FOV10_Boresight_X","CH0_FOV11_Boresight_X","CH0_FOV12_Boresight_X","CH0_FOV13_Boresight_X","0","0","0"},
            string_C10[16]={"CH0_FOV1_Boresight_Y","CH0_FOV2_Boresight_Y","CH0_FOV3_Boresight_Y","CH0_FOV4_Boresight_Y","CH0_FOV5_Boresight_Y","CH0_FOV6_Boresight_Y","CH0_FOV7_Boresight_Y","CH0_FOV8_Boresight_Y","CH0_FOV9_Boresight_Y","CH0_FOV10_Boresight_Y","CH0_FOV11_Boresight_Y","CH0_FOV12_Boresight_Y","CH0_FOV13_Boresight_Y","0","0","0"},
            string_C11[16]={"CH1_FOV1_Boresight_X","CH1_FOV2_Boresight_X","CH1_FOV3_Boresight_X","CH1_FOV4_Boresight_X","CH1_FOV5_Boresight_X","CH1_FOV6_Boresight_X","CH1_FOV7_Boresight_X","CH1_FOV8_Boresight_X","CH1_FOV9_Boresight_X","CH1_FOV10_Boresight_X","CH1_FOV11_Boresight_X","CH1_FOV12_Boresight_X","CH1_FOV13_Boresight_X","0","0","0"},
            string_C12[16]={"CH1_FOV1_Boresight_Y","CH1_FOV2_Boresight_Y","CH1_FOV3_Boresight_Y","CH1_FOV4_Boresight_Y","CH1_FOV5_Boresight_Y","CH1_FOV6_Boresight_Y","CH1_FOV7_Boresight_Y","CH1_FOV8_Boresight_Y","CH1_FOV9_Boresight_Y","CH1_FOV10_Boresight_Y","CH1_FOV11_Boresight_Y","CH1_FOV12_Boresight_Y","CH1_FOV13_Boresight_Y","0","0","0"},
            string_C13[16]={"CH2_FOV1_Boresight_X","CH2_FOV2_Boresight_X","CH2_FOV3_Boresight_X","CH2_FOV4_Boresight_X","CH2_FOV5_Boresight_X","CH2_FOV6_Boresight_X","CH2_FOV7_Boresight_X","CH2_FOV8_Boresight_X","CH2_FOV9_Boresight_X","CH2_FOV10_Boresight_X","CH2_FOV11_Boresight_X","CH2_FOV12_Boresight_X","CH2_FOV13_Boresight_X","0","0","0"},
            string_C14[16]={"CH2_FOV1_Boresight_Y","CH2_FOV2_Boresight_Y","CH2_FOV3_Boresight_Y","CH2_FOV4_Boresight_Y","CH2_FOV5_Boresight_Y","CH2_FOV6_Boresight_Y","CH2_FOV7_Boresight_Y","CH2_FOV8_Boresight_Y","CH2_FOV9_Boresight_Y","CH2_FOV10_Boresight_Y","CH2_FOV11_Boresight_Y","CH2_FOV12_Boresight_Y","CH2_FOV13_Boresight_Y","0","0","0"},
            string_C15[16]={"CH3_FOV1_Boresight_X","CH3_FOV2_Boresight_X","CH3_FOV3_Boresight_X","CH3_FOV4_Boresight_X","CH3_FOV5_Boresight_X","CH3_FOV6_Boresight_X","CH3_FOV7_Boresight_X","CH3_FOV8_Boresight_X","CH3_FOV9_Boresight_X","CH3_FOV10_Boresight_X","CH3_FOV11_Boresight_X","CH3_FOV12_Boresight_X","CH3_FOV13_Boresight_X","0","0","0"},
            string_C16[16]={"CH3_FOV1_Boresight_Y","CH3_FOV2_Boresight_Y","CH3_FOV3_Boresight_Y","CH3_FOV4_Boresight_Y","CH3_FOV5_Boresight_Y","CH3_FOV6_Boresight_Y","CH3_FOV7_Boresight_Y","CH3_FOV8_Boresight_Y","CH3_FOV9_Boresight_Y","CH3_FOV10_Boresight_Y","CH3_FOV11_Boresight_Y","CH3_FOV12_Boresight_Y","CH3_FOV13_Boresight_Y","0","0","0"},
            string_C17[16]={"CH4_FOV1_Boresight_X","CH4_FOV2_Boresight_X","CH4_FOV3_Boresight_X","CH4_FOV4_Boresight_X","CH4_FOV5_Boresight_X","CH4_FOV6_Boresight_X","CH4_FOV7_Boresight_X","CH4_FOV8_Boresight_X","CH4_FOV9_Boresight_X","CH4_FOV10_Boresight_X","CH4_FOV11_Boresight_X","CH4_FOV12_Boresight_X","CH4_FOV13_Boresight_X","0","0","0"},
            string_C18[16]={"CH4_FOV1_Boresight_Y","CH4_FOV2_Boresight_Y","CH4_FOV3_Boresight_Y","CH4_FOV4_Boresight_Y","CH4_FOV5_Boresight_Y","CH4_FOV6_Boresight_Y","CH4_FOV7_Boresight_Y","CH4_FOV8_Boresight_Y","CH4_FOV9_Boresight_Y","CH4_FOV10_Boresight_Y","CH4_FOV11_Boresight_Y","CH4_FOV12_Boresight_Y","CH4_FOV13_Boresight_Y","0","0","0"},
            string_C19[16]={"CH5_FOV1_Boresight_X","CH5_FOV2_Boresight_X","CH5_FOV3_Boresight_X","CH5_FOV4_Boresight_X","CH5_FOV5_Boresight_X","CH5_FOV6_Boresight_X","CH5_FOV7_Boresight_X","CH5_FOV8_Boresight_X","CH5_FOV9_Boresight_X","CH5_FOV10_Boresight_X","CH5_FOV11_Boresight_X","CH5_FOV12_Boresight_X","CH5_FOV13_Boresight_X","0","0","0"},
            string_C20[16]={"CH5_FOV1_Boresight_Y","CH5_FOV2_Boresight_Y","CH5_FOV3_Boresight_Y","CH5_FOV4_Boresight_Y","CH5_FOV5_Boresight_Y","CH5_FOV6_Boresight_Y","CH5_FOV7_Boresight_Y","CH5_FOV8_Boresight_Y","CH5_FOV9_Boresight_Y","CH5_FOV10_Boresight_Y","CH5_FOV11_Boresight_Y","CH5_FOV12_Boresight_Y","CH5_FOV13_Boresight_Y","0","0","0"},
            string_C21[16]={"CH0_VALIDAREA_WIDTH","CH0_VALIDAREA_HEIGHT","CH1_VALIDAREA_WIDTH","CH1_VALIDAREA_HEIGHT","CH2_VALIDAREA_WIDTH","CH2_VALIDAREA_HEIGHT","CH3_VALIDAREA_WIDTH","CH3_VALIDAREA_HEIGHT","CH4_VALIDAREA_WIDTH","CH4_VALIDAREA_HEIGHT","CH5_VALIDAREA_WIDTH","CH5_VALIDAREA_HEIGHT","FOV_CHANGE_interval","0","0","0"},
            string_C22[16]={"CH0_FOV1_ZOOM","CH0_FOV2_ZOOM","CH0_FOV3_ZOOM","CH0_FOV4_ZOOM","CH0_FOV5_ZOOM","CH0_FOV6_ZOOM","CH0_FOV7_ZOOM","CH0_FOV8_ZOOM","CH0_FOV9_ZOOM","CH0_FOV10_ZOOM","CH0_FOV11_ZOOM","CH0_FOV12_ZOOM","CH0_FOV13_ZOOM","0","0","0"},
            string_C23[16]={"CH1_FOV1_ZOOM","CH1_FOV2_ZOOM","CH1_FOV3_ZOOM","CH1_FOV4_ZOOM","CH1_FOV5_ZOOM","CH1_FOV6_ZOOM","CH1_FOV7_ZOOM","CH1_FOV8_ZOOM","CH1_FOV9_ZOOM","CH1_FOV10_ZOOM","CH1_FOV11_ZOOM","CH1_FOV12_ZOOM","CH1_FOV13_ZOOM","0","0","0"},
            string_C24[16]={"CH2_FOV1_ZOOM","CH2_FOV2_ZOOM","CH2_FOV3_ZOOM","CH2_FOV4_ZOOM","CH2_FOV5_ZOOM","CH2_FOV6_ZOOM","CH2_FOV7_ZOOM","CH2_FOV8_ZOOM","CH2_FOV9_ZOOM","CH2_FOV10_ZOOM","CH2_FOV11_ZOOM","CH2_FOV12_ZOOM","CH2_FOV13_ZOOM","0","0","0"},
            string_C25[16]={"CH3_FOV1_ZOOM","CH3_FOV2_ZOOM","CH3_FOV3_ZOOM","CH3_FOV4_ZOOM","CH3_FOV5_ZOOM","CH3_FOV6_ZOOM","CH3_FOV7_ZOOM","CH3_FOV8_ZOOM","CH3_FOV9_ZOOM","CH3_FOV10_ZOOM","CH3_FOV11_ZOOM","CH3_FOV12_ZOOM","CH3_FOV13_ZOOM","0","0","0"},
            string_C26[16]={"CH4_FOV1_ZOOM","CH4_FOV2_ZOOM","CH4_FOV3_ZOOM","CH4_FOV4_ZOOM","CH4_FOV5_ZOOM","CH4_FOV6_ZOOM","CH4_FOV7_ZOOM","CH4_FOV8_ZOOM","CH4_FOV9_ZOOM","CH4_FOV10_ZOOM","CH4_FOV11_ZOOM","CH4_FOV12_ZOOM","CH4_FOV13_ZOOM","0","0","0"},
            string_C27[16]={"CH5_FOV1_ZOOM","CH5_FOV2_ZOOM","CH5_FOV3_ZOOM","CH5_FOV4_ZOOM","CH5_FOV5_ZOOM","CH5_FOV6_ZOOM","CH5_FOV7_ZOOM","CH5_FOV8_ZOOM","CH5_FOV9_ZOOM","CH5_FOV10_ZOOM","CH5_FOV11_ZOOM","CH5_FOV12_ZOOM","CH5_FOV13_ZOOM","0","0","0"}

     ;

signals:
    void copy_Done();
    void socket_copy_Done();
    void toProgrammer();//用于跳转到Programmer界面的信号
};



#endif // DIALOG_H
