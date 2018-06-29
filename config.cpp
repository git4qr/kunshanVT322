#include "dialog.h"
#include "QDebug"
#include <QFormLayout>
#include <QTabWidget>
#include <QFile>


void Dialog::doubleclick(QListWidgetItem *item)
{
    QString s_item = item->text();
    if(s_item.compare("1-R/T Ctrl 1")==0)
    {
        qDebug()<<"1:"<<s_item;
        dialog_c1.show();
    }
    else if(s_item.compare("2-Acquire Mode")==0)
    {
        qDebug()<<"2:"<<s_item;
        dialog_c2.show();
    }
    else if(s_item.compare("3-Track Mode")==0)
    {
        qDebug()<<"3:"<<s_item;
        dialog_c3.show();
    }
    else if(s_item.compare("4-Cent Alg 1")==0)
    {
        qDebug()<<"4:"<<s_item;
        dialog_c4.show();
    }
}
void Dialog::init_dialog_c1()
{
    dialog_c1.setWindowTitle(tr("1-R/T Ctrl 1"));
    upd_c1 = new QPushButton();
    def_c1 = new QPushButton();
    labelt_c1 = new QLabel();
    box1_c1 = new QComboBox();
    box2_c1 = new QComboBox();
    checkBox3_c1 = new QCheckBox();
    lineEdit4_c1 = new QLineEdit();
    box5_c1 = new QComboBox();
    lineEdit6_c1 = new QLineEdit();
    lineEdit7_c1 = new QLineEdit();
    lineEdit8_c1 = new QLineEdit();
    lineEdit9_c1 = new QLineEdit();
    lineEdit10_c1 = new QLineEdit();
    upd_c1->setText("刷新");
    def_c1->setText("默认");
    labelt_c1->setText("Block 1: Real-time Control 1");
    box1_c1->addItem("[0] Acquisition Mode");
    box1_c1->addItem("[1] Track Mode");
    box1_c1->addItem("[2] Run AVT BIT");
    box1_c1->addItem("[3] Config Changing");
    box1_c1->addItem("[4] BIT Failed");
    box2_c1->addItem("[0] Sensor 1");
    box2_c1->addItem("[1] Sensor 2");
    box2_c1->addItem("[2] Sensor 3");
    box2_c1->addItem("[3] Sensor 4");
    box5_c1->addItem("[0] Off");
    box5_c1->addItem("[1] External");
    QVBoxLayout *vlayout1 = new QVBoxLayout;
    vlayout1->addWidget(upd_c1);
    vlayout1->addWidget(def_c1);
    QHBoxLayout *hlayout0 = new QHBoxLayout;
    hlayout0->addLayout(vlayout1);
    hlayout0->addWidget(labelt_c1);
    QFormLayout *pLayout = new QFormLayout();
    pLayout->addRow(QStringLiteral("Enable Autotrack"), box1_c1);
    pLayout->addRow(QStringLiteral("Select Video Sensor"), box2_c1);
    pLayout->addRow(QStringLiteral("Enable BG Scenelock"), checkBox3_c1);
    pLayout->addRow(QStringLiteral("Symbology Intensity"), lineEdit4_c1);
    pLayout->addRow(QStringLiteral("LOS Usage Selection"), box5_c1);
    pLayout->addRow(QStringLiteral("LOS Latency"), lineEdit6_c1);
    pLayout->addRow(QStringLiteral("LOS Azimuth Rate"), lineEdit7_c1);
    pLayout->addRow(QStringLiteral("LOS Elevation Rate"), lineEdit8_c1);
    pLayout->addRow(QStringLiteral("LOS Azimuth Position"), lineEdit9_c1);
    pLayout->addRow(QStringLiteral("LOS Elevation Position"), lineEdit10_c1);
    QVBoxLayout *vlayout2 = new QVBoxLayout;
    vlayout2->addLayout(hlayout0);
    vlayout2->addLayout(pLayout);
    dialog_c1.setLayout(vlayout2);
}
void Dialog::init_dialog_c2()
{
    dialog_c2.setWindowTitle(tr("2-Acquire Mode"));
    upd_c2 = new QPushButton();
    def_c2 = new QPushButton();
    labelt_c2 = new QLabel();
    box1_c2 = new QComboBox();
    box2_c2 = new QComboBox();
    box3_c2 = new QComboBox();
    box4_c2 = new QComboBox();
    lineEdit5_c2 = new QLineEdit();
    lineEdit6_c2 = new QLineEdit();
    lineEdit7_c2 = new QLineEdit();
    lineEdit8_c2 = new QLineEdit();
    lineEdit9_c2 = new QLineEdit();
    lineEdit10_c2 = new QLineEdit();
    lineEdit11_c2 = new QLineEdit();
    checkBox12_c2 = new QCheckBox();
    checkBox13_c2 = new QCheckBox();
    box14_c2 = new QComboBox();
    upd_c2->setText("刷新");
    def_c2->setText("默认");
    labelt_c2->setText("Block 2: Acquisition Mode");
    box1_c2->addItem("[0] Centroid");
    box1_c2->addItem("[1] Correlation");
    box1_c2->addItem("[2] MTT");
    box1_c2->addItem("[3] Edge");
    box1_c2->addItem("[4] Scenelock");
    box1_c2->addItem("[5] Phase Corr");
    box1_c2->addItem("[7] MTD");
    box2_c2->addItem("[0] None");
    box2_c2->addItem("[1] Position");
    box2_c2->addItem("[2] Size");
    box2_c2->addItem("[3] Speed");
    box2_c2->addItem("[5] Intensity");
    box3_c2->addItem("[0] Bipolar Contrast");
    box3_c2->addItem("[1] Positive Contrast");
    box3_c2->addItem("[2] Negative Contrast");
    box3_c2->addItem("[3] Automatic");
    box4_c2->addItem("[0] Manual Threshold");
    box4_c2->addItem("[1] Manual Offset");
    box4_c2->addItem("[2] Automatic");
    box14_c2->addItem("[0] Arm Disabled");
    box14_c2->addItem("[1] Arm Enabled");
    box14_c2->addItem("[2] Reversionary Trk");
    QVBoxLayout *vlayout1 = new QVBoxLayout;
    vlayout1->addWidget(upd_c2);
    vlayout1->addWidget(def_c2);
    QHBoxLayout *hlayout0 = new QHBoxLayout;
    hlayout0->addLayout(vlayout1);
    hlayout0->addWidget(labelt_c2);
    QFormLayout *pLayout = new QFormLayout();
    pLayout->addRow(QStringLiteral("Acquisition Algorithm"), box1_c2);
    pLayout->addRow(QStringLiteral("Acquisition Target Select"), box2_c2);
    pLayout->addRow(QStringLiteral("Acquisition Target Polarity"), box3_c2);
    pLayout->addRow(QStringLiteral("Acquisition Preproc Threshold Mode"), box4_c2);
    pLayout->addRow(QStringLiteral("Acquisition Preproc Manual Offset"), lineEdit5_c2);
    pLayout->addRow(QStringLiteral("Acquisition Window Position X"), lineEdit6_c2);
    pLayout->addRow(QStringLiteral("Acquisition Window Position Y"), lineEdit7_c2);
    pLayout->addRow(QStringLiteral("Acquisition Window Size X"), lineEdit8_c2);
    pLayout->addRow(QStringLiteral("Acquisition Window Size Y"), lineEdit9_c2);
    pLayout->addRow(QStringLiteral("Switch To Next Acquire Target"), lineEdit10_c2);
    pLayout->addRow(QStringLiteral("Switch To Acquire Target 'n'"), lineEdit11_c2);
    pLayout->addRow(QStringLiteral("Acquisition Window Symbology"), checkBox12_c2);
    pLayout->addRow(QStringLiteral("Acquisition Aimpoint Symbology"), checkBox13_c2);
    pLayout->addRow(QStringLiteral("'Armed' Acquisition Mode"), box14_c2);
    QVBoxLayout *vlayout2 = new QVBoxLayout;
    vlayout2->addLayout(hlayout0);
    vlayout2->addLayout(pLayout);
    dialog_c2.setLayout(vlayout2);
}
void Dialog::init_dialog_c3()
{
    dialog_c3.setWindowTitle(tr("3-Track Mode"));
}
void Dialog::init_dialog_c4()
{
    dialog_c4.setWindowTitle(tr("4-Cent Alg 1"));
}

void Dialog::init_dialog()
{
    init_dialog_config();//配置平台参数
    init_dialog_PID();//配置PID
    init_dialog_JosHandle();//配置手柄控制
    init_dialog_JosMap1();//手柄按键映射1
    init_dialog_JosMap2();//手柄按键映射2
    init_dialog_KeyboardMap1();//键盘按键映射1
    init_dialog_KeyboardMap2();//键盘按键映射2
    init_dialog_SerialParam();//串口参数配置
    init_dialog_UTCParam1();//UTC参数配置1
    init_dialog_UTCParam2();//UTC参数配置2
    init_dialog_UTCParam3();//UTC参数配置3
    init_dialog_EMParam();//增强和多目标算法配置
    init_dialog_OSDParam1();//OSD参数配置1
    init_dialog_OSDParam2();//OSD参数配置2
    init_dialog_OSDParam3();//OSD参数配置3
    init_dialog_CameraParam1();//相机参数1
    init_dialog_CameraParam2();//相机参数2
    init_dialog_CameraParam3();
    init_dialog_CameraParam4();
    init_dialog_CameraParam5();
    init_dialog_CameraParam6();
    init_dialog_CameraParam7();
    init_dialog_CameraParam8();
    init_dialog_CameraParam9();
    init_dialog_CameraParam10();
    init_dialog_CameraParam11();
    init_dialog_CameraParam12();
    init_dialog_CameraParam13();
    init_dialog_CameraParam14();
    init_dialog_CameraParam15();
    init_dialog_CameraParam16();
    init_dialog_CameraParam17();
    init_dialog_CameraParam18();
    init_dialog_CameraParam19();
    init_dialog_CameraParam20();
    init_dialog_CameraParam21();
    init_dialog_CameraParam22();
    init_dialog_CameraParam23();
    init_dialog_CameraParam24();
    init_dialog_CameraParam25();
    init_dialog_CameraParam26();
    init_dialog_CameraParam27();
}

void Dialog::init_dialog_config()
{
   // qDebug()<<"init _dialog_config";
    dialog_config.setWindowTitle(tr("平台配置"));

    dialog_config.setGeometry(QRect(1170, 123, 357, 614));
//-------------------------
    tabWidget = new QTabWidget();
    tabWidget->setObjectName(QStringLiteral("tabWidget"));
    tabWidget->setGeometry(QRect(0, 0,331, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tableWidget_Profile = new QTableWidget(tab);
    tableWidget_Profile->horizontalHeader()->setStretchLastSection(true);
    tableWidget_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tableWidget_Profile->setGeometry(QRect(0, 0, 450, 614));
    tabWidget->addTab(tab, QString());


    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));

    init_table_Profile();


    connect(tableWidget_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tableWidget_Profile_itemChanged(QTableWidgetItem*)));
    connect(tableWidget_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tableWidget_Profile_itemActivated(QTableWidgetItem*)));


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget);
    dialog_config.setLayout(vlayout);

}
void Dialog::init_dialog_PID()
{
    dialog_pid.setWindowTitle(tr("PID配置"));
    dialog_pid.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabwidget_pid = new QTabWidget();
    tabwidget_pid->setObjectName(QStringLiteral("tabWidget"));
    tabwidget_pid->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabwidget_pid_Profile = new QTableWidget(tab);
    tabwidget_pid_Profile->horizontalHeader()->setStretchLastSection(true);
    tabwidget_pid_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabwidget_pid_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabwidget_pid->addTab(tab, QString());
    tabwidget_pid->setTabText(tabwidget_pid->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabwidget_pid_Profile->setRowCount(16);
    tabwidget_pid_Profile->setColumnCount(2);
    tabwidget_pid_Profile->setColumnWidth(0,90);
    tabwidget_pid_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>15&&i<32){
            tabwidget_pid_Profile->setItem(i%16,0, new QTableWidgetItem(string_pid[i%16]));
            tabwidget_pid_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabwidget_pid_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabwidget_pid_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabwidget_pid_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabwidget_pid_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabwidget_pid);
    dialog_pid.setLayout(vlayout);
}
void Dialog::init_dialog_JosHandle()
{
    dialog_JosHandle.setWindowTitle(tr("JosHandle配置"));
    dialog_JosHandle.setGeometry(QRect(1170, 123, 450, 614));
//-------------------------
    tabWidget_JosHandle = new QTabWidget();
    tabWidget_JosHandle->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_JosHandle->setGeometry(QRect(0, 0, 450, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_JosHandle_Profile = new QTableWidget(tab);
    tabWidget_JosHandle_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_JosHandle_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_JosHandle_Profile->setGeometry(QRect(0, 0, 450, 614));
    tabWidget_JosHandle->addTab(tab, QString());
    tabWidget_JosHandle->setTabText(tabWidget_JosHandle->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_JosHandle_Profile->setRowCount(16);
    tabWidget_JosHandle_Profile->setColumnCount(2);
    tabWidget_JosHandle_Profile->setColumnWidth(0,200);
    tabWidget_JosHandle_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>31&&i<48){
            tabWidget_JosHandle_Profile->setItem(i%16,0, new QTableWidgetItem(string_JosHandle[i%16]));
            tabWidget_JosHandle_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_JosHandle_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_JosHandle_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_JosHandle_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_JosHandle_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_JosHandle);
    dialog_JosHandle.setLayout(vlayout);
}

void Dialog::init_dialog_JosMap1()
{
    dialog_Josmap1.setWindowTitle(tr("JosMap1配置"));
    dialog_Josmap1.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_Josmap1 = new QTabWidget();
    tabWidget_Josmap1->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_Josmap1->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_Josmap1_Profile = new QTableWidget(tab);
    tabWidget_Josmap1_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_Josmap1_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_Josmap1_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_Josmap1->addTab(tab, QString());
    tabWidget_Josmap1->setTabText(tabWidget_JosHandle->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_Josmap1_Profile->setRowCount(16);
    tabWidget_Josmap1_Profile->setColumnCount(2);
    tabWidget_Josmap1_Profile->setColumnWidth(0,90);
    tabWidget_Josmap1_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>47&&i<64){
            tabWidget_Josmap1_Profile->setItem(i%16,0, new QTableWidgetItem(string_JosMap1[i%16]));
            tabWidget_Josmap1_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_Josmap1_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_Josmap1_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_Josmap1_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_Josmap1_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_Josmap1);
    dialog_Josmap1.setLayout(vlayout);
}

void Dialog::init_dialog_JosMap2()
{
    dialog_Josmap2.setWindowTitle(tr("JosMap2配置"));
    dialog_Josmap2.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_Josmap2 = new QTabWidget();
    tabWidget_Josmap2->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_Josmap2->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_Josmap2_Profile = new QTableWidget(tab);
    tabWidget_Josmap2_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_Josmap2_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_Josmap2->addTab(tab, QString());
    tabWidget_Josmap2->setTabText(tabWidget_Josmap2->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_Josmap2_Profile->setRowCount(16);
    tabWidget_Josmap2_Profile->setColumnCount(2);
    tabWidget_Josmap2_Profile->setColumnWidth(0,90);
    tabWidget_Josmap2_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>63&&i<80){
            tabWidget_Josmap2_Profile->setItem(i%16,0, new QTableWidgetItem(string_JosMap2[i%16]));
            tabWidget_Josmap2_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_Josmap2_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_Josmap2_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_Josmap2_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_Josmap2_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_Josmap2);
    dialog_Josmap2.setLayout(vlayout);
}

void Dialog::init_dialog_KeyboardMap1()
{
    dialog_Keyboardmap1.setWindowTitle(tr("KeyboardMap1配置"));
    dialog_Keyboardmap1.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_Keyboardmap1 = new QTabWidget();
    tabWidget_Keyboardmap1->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_Keyboardmap1->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_Keyboardmap1_Profile = new QTableWidget(tab);
    tabWidget_Keyboardmap1_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_Keyboardmap1_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_Keyboardmap1->addTab(tab, QString());
    tabWidget_Keyboardmap1->setTabText(tabWidget_Keyboardmap1->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_Keyboardmap1_Profile->setRowCount(16);
    tabWidget_Keyboardmap1_Profile->setColumnCount(2);
    tabWidget_Keyboardmap1_Profile->setColumnWidth(0,90);
    tabWidget_Keyboardmap1_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>79&&i<96){
            tabWidget_Keyboardmap1_Profile->setItem(i%16,0, new QTableWidgetItem(string_Key1[i%16]));
            tabWidget_Keyboardmap1_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_Keyboardmap1_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_Keyboardmap1_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_Keyboardmap1_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_Keyboardmap1_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_Keyboardmap1);
    dialog_Keyboardmap1.setLayout(vlayout);
}

void Dialog::init_dialog_KeyboardMap2()
{
    dialog_Keyboardmap2.setWindowTitle(tr("KeyboardMap2配置"));
    dialog_Keyboardmap2.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_Keyboardmap2 = new QTabWidget();
    tabWidget_Keyboardmap2->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_Keyboardmap2->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_Keyboardmap2_Profile = new QTableWidget(tab);
    tabWidget_Keyboardmap2_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_Keyboardmap2_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_Keyboardmap2->addTab(tab, QString());
    tabWidget_Keyboardmap2->setTabText(tabWidget_Keyboardmap2->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_Keyboardmap2_Profile->setRowCount(16);
    tabWidget_Keyboardmap2_Profile->setColumnCount(2);
    tabWidget_Keyboardmap2_Profile->setColumnWidth(0,90);
    tabWidget_Keyboardmap2_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>95&&i<112){
            tabWidget_Keyboardmap2_Profile->setItem(i%16,0, new QTableWidgetItem(string_Key2[i%16]));
            tabWidget_Keyboardmap2_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_Keyboardmap2_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_Keyboardmap2_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_Keyboardmap2_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_Keyboardmap2_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_Keyboardmap2);
    dialog_Keyboardmap2.setLayout(vlayout);
}

void Dialog::init_dialog_SerialParam()
{
    dialog_SerialParam.setWindowTitle(tr("SerialParam配置"));
    dialog_SerialParam.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_SerialParam = new QTabWidget();
    tabWidget_SerialParam->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_SerialParam->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_SerialParam_Profile = new QTableWidget(tab);
    tabWidget_SerialParam_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_SerialParam_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_SerialParam->addTab(tab, QString());
    tabWidget_SerialParam->setTabText(tabWidget_SerialParam->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_SerialParam_Profile->setRowCount(16);
    tabWidget_SerialParam_Profile->setColumnCount(2);
    tabWidget_SerialParam_Profile->setColumnWidth(0,90);
    tabWidget_SerialParam_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>111&&i<128){
            tabWidget_SerialParam_Profile->setItem(i%16,0, new QTableWidgetItem(string_Serial[i%16]));
            tabWidget_SerialParam_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_SerialParam_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_SerialParam_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_SerialParam_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_SerialParam_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_SerialParam);
    dialog_SerialParam.setLayout(vlayout);
}

void Dialog::init_dialog_UTCParam1()
{
    dialog_UTCParam1.setWindowTitle(tr("UTCParam1配置"));
    dialog_UTCParam1.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_UTCParam1 = new QTabWidget();
    tabWidget_UTCParam1->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_UTCParam1->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_UTCParam1_Profile = new QTableWidget(tab);
    tabWidget_UTCParam1_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_UTCParam1_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_UTCParam1_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_UTCParam1->addTab(tab, QString());
    tabWidget_UTCParam1->setTabText(tabWidget_UTCParam1->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_UTCParam1_Profile->setRowCount(16);
    tabWidget_UTCParam1_Profile->setColumnCount(2);
    tabWidget_UTCParam1_Profile->setColumnWidth(0,180);
    tabWidget_UTCParam1_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>127&&i<144){
            tabWidget_UTCParam1_Profile->setItem(i%16,0, new QTableWidgetItem(string_UTC1[i%16]));
            tabWidget_UTCParam1_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_UTCParam1_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam1_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_UTCParam1_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam1_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_UTCParam1);
    dialog_UTCParam1.setLayout(vlayout);
}

void Dialog::init_dialog_UTCParam2()
{
    dialog_UTCParam2.setWindowTitle(tr("UTCParam2配置"));
    dialog_UTCParam2.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_UTCParam2 = new QTabWidget();
    tabWidget_UTCParam2->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_UTCParam2->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_UTCParam2_Profile = new QTableWidget(tab);
    tabWidget_UTCParam2_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_UTCParam2_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_UTCParam2_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_UTCParam2->addTab(tab, QString());
    tabWidget_UTCParam2->setTabText(tabWidget_UTCParam2->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_UTCParam2_Profile->setRowCount(16);
    tabWidget_UTCParam2_Profile->setColumnCount(2);
    tabWidget_UTCParam2_Profile->setColumnWidth(0,180);
    tabWidget_UTCParam2_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>143&&i<160){
            tabWidget_UTCParam2_Profile->setItem(i%16,0, new QTableWidgetItem(string_UTC2[i%16]));
            tabWidget_UTCParam2_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_UTCParam2_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam2_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_UTCParam2_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam2_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_UTCParam2);
    dialog_UTCParam2.setLayout(vlayout);
}

void Dialog::init_dialog_UTCParam3()
{
    dialog_UTCParam3.setWindowTitle(tr("UTCParam3配置"));
    dialog_UTCParam3.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_UTCParam3 = new QTabWidget();
    tabWidget_UTCParam3->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_UTCParam3->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_UTCParam3_Profile = new QTableWidget(tab);
    tabWidget_UTCParam3_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_UTCParam3_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_UTCParam3_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_UTCParam3->addTab(tab, QString());
    tabWidget_UTCParam3->setTabText(tabWidget_UTCParam3->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_UTCParam3_Profile->setRowCount(16);
    tabWidget_UTCParam3_Profile->setColumnCount(2);
    tabWidget_UTCParam3_Profile->setColumnWidth(0,180);
    tabWidget_UTCParam3_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>159&&i<176){
            tabWidget_UTCParam3_Profile->setItem(i%16,0, new QTableWidgetItem(string_UTC3[i%16]));
            tabWidget_UTCParam3_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_UTCParam3_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam3_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_UTCParam3_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_UTCParam3_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_UTCParam3);
    dialog_UTCParam3.setLayout(vlayout);
}

void Dialog::init_dialog_EMParam()
{
    dialog_EMParam.setWindowTitle(tr("ENH&MMT配置"));
    dialog_EMParam.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_EMParam = new QTabWidget();
    tabWidget_EMParam->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_EMParam->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_EMParam_Profile = new QTableWidget(tab);
    tabWidget_EMParam_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_EMParam_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_EMParam_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_EMParam->addTab(tab, QString());
    tabWidget_EMParam->setTabText(tabWidget_EMParam->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_EMParam_Profile->setRowCount(16);
    tabWidget_EMParam_Profile->setColumnCount(2);
    tabWidget_EMParam_Profile->setColumnWidth(0,180);
    tabWidget_EMParam_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>175&&i<192){
            tabWidget_EMParam_Profile->setItem(i%16,0, new QTableWidgetItem(string_EM[i%16]));
            tabWidget_EMParam_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_EMParam_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_EMParam_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_EMParam_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_EMParam_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_EMParam);
    dialog_EMParam.setLayout(vlayout);
}

void Dialog::init_dialog_OSDParam1()
{

    dialog_OSDParam1.setWindowTitle(tr("OSDParam1配置"));
    dialog_OSDParam1.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_OSDParam1 = new QTabWidget();
    tabWidget_OSDParam1->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_OSDParam1->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_OSDParam1_Profile = new QTableWidget(tab);
    tabWidget_OSDParam1_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_OSDParam1_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_OSDParam1_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_OSDParam1->addTab(tab, QString());
    tabWidget_OSDParam1->setTabText(tabWidget_OSDParam1->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_OSDParam1_Profile->setRowCount(16);
    tabWidget_OSDParam1_Profile->setColumnCount(2);
    tabWidget_OSDParam1_Profile->setColumnWidth(0,180);
    tabWidget_OSDParam1_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>191&&i<208){
            tabWidget_OSDParam1_Profile->setItem(i%16,0, new QTableWidgetItem(string_OSD1[i%16]));
            tabWidget_OSDParam1_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_OSDParam1_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam1_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_OSDParam1_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam1_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_OSDParam1);
    dialog_OSDParam1.setLayout(vlayout);
}

void Dialog::init_dialog_OSDParam2()
{
    dialog_OSDParam2.setWindowTitle(tr("OSDParam2配置"));
    dialog_OSDParam2.setGeometry(QRect(1170, 123, 320, 614));
//-------------------------
    tabWidget_OSDParam2 = new QTabWidget();
    tabWidget_OSDParam2->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_OSDParam2->setGeometry(QRect(0, 0, 320, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_OSDParam2_Profile = new QTableWidget(tab);
    tabWidget_OSDParam2_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_OSDParam2_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_OSDParam2_Profile->setGeometry(QRect(0, 0, 320, 614));
    tabWidget_OSDParam2->addTab(tab, QString());
    tabWidget_OSDParam2->setTabText(tabWidget_OSDParam2->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_OSDParam2_Profile->setRowCount(16);
    tabWidget_OSDParam2_Profile->setColumnCount(2);
    tabWidget_OSDParam2_Profile->setColumnWidth(0,150);
    tabWidget_OSDParam2_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>207&&i<224){
            tabWidget_OSDParam2_Profile->setItem(i%16,0, new QTableWidgetItem(string_OSD2[i%16]));
            tabWidget_OSDParam2_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_OSDParam2_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam2_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_OSDParam2_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam2_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_OSDParam2);
    dialog_OSDParam2.setLayout(vlayout);

}

void Dialog::init_dialog_OSDParam3()
{
    dialog_OSDParam3.setWindowTitle(tr("OSDParam3配置"));
    dialog_OSDParam3.setGeometry(QRect(1170, 123, 250, 614));
//-------------------------
    tabWidget_OSDParam3 = new QTabWidget();
    tabWidget_OSDParam3->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_OSDParam3->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_OSDParam3_Profile = new QTableWidget(tab);
    tabWidget_OSDParam3_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_OSDParam3_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_OSDParam3_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_OSDParam3->addTab(tab, QString());
    tabWidget_OSDParam3->setTabText(tabWidget_OSDParam3->indexOf(tab), QApplication::translate("Dialog", "profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_OSDParam3_Profile->setRowCount(16);
    tabWidget_OSDParam3_Profile->setColumnCount(2);
    tabWidget_OSDParam3_Profile->setColumnWidth(0,120);
    tabWidget_OSDParam3_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>223&&i<240){
            tabWidget_OSDParam3_Profile->setItem(i%16,0, new QTableWidgetItem(string_OSD3[i%16]));
            tabWidget_OSDParam3_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_OSDParam3_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam3_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_OSDParam3_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_OSDParam3_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_OSDParam3);
    dialog_OSDParam3.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam1()
{
    dialog_CameraParam1.setWindowTitle(tr("CameraParam1配置"));
    dialog_CameraParam1.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_CameraParam1 = new QTabWidget();
    tabWidget_CameraParam1->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam1->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam1_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam1_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam1_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam1_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam1->addTab(tab, QString());
    tabWidget_CameraParam1->setTabText(tabWidget_CameraParam1->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam1_camera_Profile->setRowCount(16);
    tabWidget_CameraParam1_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam1_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam1_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            tabWidget_CameraParam1_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C1[i%16]));
            tabWidget_CameraParam1_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam1_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam1_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam1_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam1_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam1);
    dialog_CameraParam1.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam2()
{
    dialog_CameraParam2.setWindowTitle(tr("CameraParam2配置"));
    dialog_CameraParam2.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam2 = new QTabWidget();
    tabWidget_CameraParam2->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam2->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam2_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam2_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam2_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam2->addTab(tab, QString());
    tabWidget_CameraParam2->setTabText(tabWidget_CameraParam2->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam2_camera_Profile->setRowCount(16);
    tabWidget_CameraParam2_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam2_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam2_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>15&&i<32){
            tabWidget_CameraParam2_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C2[i%16]));
            tabWidget_CameraParam2_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam2_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam2_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam2_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam2_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam2);
    dialog_CameraParam2.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam3()
{
    dialog_CameraParam3.setWindowTitle(tr("CameraParam3配置"));
    dialog_CameraParam3.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam3 = new QTabWidget();
    tabWidget_CameraParam3->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam3->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam3_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam3_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam3_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam3->addTab(tab, QString());
    tabWidget_CameraParam3->setTabText(tabWidget_CameraParam3->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam3_camera_Profile->setRowCount(16);
    tabWidget_CameraParam3_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam3_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam3_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>31&&i<48){
            tabWidget_CameraParam3_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C3[i%16]));
            tabWidget_CameraParam3_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam3_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam3_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam3_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam3_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam3);
    dialog_CameraParam3.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam4()
{
    dialog_CameraParam4.setWindowTitle(tr("CameraParam4配置"));
    dialog_CameraParam4.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam4 = new QTabWidget();
    tabWidget_CameraParam4->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam4->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam4_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam4_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam4_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam4->addTab(tab, QString());
    tabWidget_CameraParam4->setTabText(tabWidget_CameraParam2->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam4_camera_Profile->setRowCount(16);
    tabWidget_CameraParam4_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam4_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam4_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>47&&i<64){
            tabWidget_CameraParam4_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C4[i%16]));
            tabWidget_CameraParam4_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam4_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam4_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam4_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam4_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam4);
    dialog_CameraParam4.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam5()
{
    dialog_CameraParam5.setWindowTitle(tr("CameraParam5配置"));
    dialog_CameraParam5.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam5 = new QTabWidget();
    tabWidget_CameraParam5->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam5->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam5_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam5_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam5_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam5->addTab(tab, QString());
    tabWidget_CameraParam5->setTabText(tabWidget_CameraParam5->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam5_camera_Profile->setRowCount(16);
    tabWidget_CameraParam5_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam5_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam5_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>63&&i<80){
            tabWidget_CameraParam5_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C5[i%16]));
            tabWidget_CameraParam5_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam5_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam5_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam5_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam5_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam5);
    dialog_CameraParam5.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam6()
{
    dialog_CameraParam6.setWindowTitle(tr("CameraParam6配置"));
    dialog_CameraParam6.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam6 = new QTabWidget();
    tabWidget_CameraParam6->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam6->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam6_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam6_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam6_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam6->addTab(tab, QString());
    tabWidget_CameraParam6->setTabText(tabWidget_CameraParam6->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam6_camera_Profile->setRowCount(16);
    tabWidget_CameraParam6_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam6_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam6_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>79&&i<96){
            tabWidget_CameraParam6_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C6[i%16]));
            tabWidget_CameraParam6_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam6_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam6_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam6_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam6_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam6);
    dialog_CameraParam6.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam7()
{
    dialog_CameraParam7.setWindowTitle(tr("CameraParam7配置"));
    dialog_CameraParam7.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam7 = new QTabWidget();
    tabWidget_CameraParam7->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam7->setGeometry(QRect(0, 0, 231, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam7_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam7_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam7_camera_Profile->setGeometry(QRect(0, 0, 231, 614));
    tabWidget_CameraParam7->addTab(tab, QString());
    tabWidget_CameraParam7->setTabText(tabWidget_CameraParam7->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam7_camera_Profile->setRowCount(16);
    tabWidget_CameraParam7_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam7_camera_Profile->setColumnWidth(0,90);
    tabWidget_CameraParam7_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>95&&i<112){
            tabWidget_CameraParam7_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C7[i%16]));
            tabWidget_CameraParam7_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam7_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam7_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam7_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam7_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam7);
    dialog_CameraParam7.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam8()
{
    dialog_CameraParam8.setWindowTitle(tr("CameraParam8配置"));
    dialog_CameraParam8.setGeometry(QRect(1170, 123, 257, 614));
//-------------------------
    tabWidget_CameraParam8 = new QTabWidget();
    tabWidget_CameraParam8->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam8->setGeometry(QRect(0, 0, 251, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam8_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam8_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam8_camera_Profile->setGeometry(QRect(0, 0, 251, 614));
    tabWidget_CameraParam8->addTab(tab, QString());
    tabWidget_CameraParam8->setTabText(tabWidget_CameraParam8->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam8_camera_Profile->setRowCount(16);
    tabWidget_CameraParam8_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam8_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam8_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>111&&i<128){
            tabWidget_CameraParam8_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C8[i%16]));
            tabWidget_CameraParam8_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam8_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam8_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam8_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam8_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam8);
    dialog_CameraParam8.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam9()
{
    dialog_CameraParam9.setWindowTitle(tr("CameraParam9配置"));
    dialog_CameraParam9.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_CameraParam9 = new QTabWidget();
    tabWidget_CameraParam9->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam9->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam9_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam9_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam9_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam9_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam9->addTab(tab, QString());
    tabWidget_CameraParam9->setTabText(tabWidget_CameraParam9->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam9_camera_Profile->setRowCount(16);
    tabWidget_CameraParam9_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam9_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam9_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>127&&i<144){
            tabWidget_CameraParam9_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C9[i%16]));
            tabWidget_CameraParam9_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam9_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam9_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam9_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam9_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam9);
    dialog_CameraParam9.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam10()
{
    dialog_CameraParam10.setWindowTitle(tr("CameraParam10配置"));
    dialog_CameraParam10.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_CameraParam10 = new QTabWidget();
    tabWidget_CameraParam10->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam10->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam10_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam10_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam10_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam10_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam10->addTab(tab, QString());
    tabWidget_CameraParam10->setTabText(tabWidget_CameraParam10->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam10_camera_Profile->setRowCount(16);
    tabWidget_CameraParam10_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam10_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam10_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>143&&i<160){
            tabWidget_CameraParam10_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C10[i%16]));
            tabWidget_CameraParam10_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam10_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam10_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam10_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam10_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam10);
    dialog_CameraParam10.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam11()
{
    dialog_CameraParam11.setWindowTitle(tr("CameraParam11配置"));
    dialog_CameraParam11.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_CameraParam11 = new QTabWidget();
    tabWidget_CameraParam11->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam11->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam11_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam11_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam11_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam11_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam11->addTab(tab, QString());
    tabWidget_CameraParam11->setTabText(tabWidget_CameraParam11->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam11_camera_Profile->setRowCount(16);
    tabWidget_CameraParam11_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam11_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam11_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>159&&i<176){
            tabWidget_CameraParam11_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C11[i%16]));
            tabWidget_CameraParam11_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam11_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam11_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam11_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam11_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam11);
    dialog_CameraParam11.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam12()
{
    dialog_CameraParam12.setWindowTitle(tr("CameraParam12配置"));
    dialog_CameraParam12.setGeometry(QRect(1170, 123, 400, 614));
//-------------------------
    tabWidget_CameraParam12 = new QTabWidget();
    tabWidget_CameraParam12->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam12->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam12_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam12_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam12_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam12_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam12->addTab(tab, QString());
    tabWidget_CameraParam12->setTabText(tabWidget_CameraParam12->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam12_camera_Profile->setRowCount(16);
    tabWidget_CameraParam12_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam12_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam12_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>175&&i<192){
            tabWidget_CameraParam12_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C12[i%16]));
            tabWidget_CameraParam12_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam12_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam12_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam12_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam12_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam12);
    dialog_CameraParam12.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam13()
{
    dialog_CameraParam13.setWindowTitle(tr("CameraParam13配置"));
    dialog_CameraParam13.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam13 = new QTabWidget();
    tabWidget_CameraParam13->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam13->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam13_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam13_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam13_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam13_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam13->addTab(tab, QString());
    tabWidget_CameraParam13->setTabText(tabWidget_CameraParam13->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam13_camera_Profile->setRowCount(16);
    tabWidget_CameraParam13_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam13_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam13_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>191&&i<208){
            tabWidget_CameraParam13_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C13[i%16]));
            tabWidget_CameraParam13_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam13_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam13_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam13_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam13_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam13);
    dialog_CameraParam13.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam14()
{
    dialog_CameraParam14.setWindowTitle(tr("CameraParam14配置"));
    dialog_CameraParam14.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam14 = new QTabWidget();
    tabWidget_CameraParam14->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam14->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam14_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam14_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam14_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam14_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam14->addTab(tab, QString());
    tabWidget_CameraParam14->setTabText(tabWidget_CameraParam14->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam14_camera_Profile->setRowCount(16);
    tabWidget_CameraParam14_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam14_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam14_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>207&&i<224){
            tabWidget_CameraParam14_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C14[i%16]));
            tabWidget_CameraParam14_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam14_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam14_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam14_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam14_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam14);
    dialog_CameraParam14.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam15()
{
    dialog_CameraParam15.setWindowTitle(tr("CameraParam15配置"));
    dialog_CameraParam15.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam15 = new QTabWidget();
    tabWidget_CameraParam15->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam15->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam15_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam15_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam15_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam15_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam15->addTab(tab, QString());
    tabWidget_CameraParam15->setTabText(tabWidget_CameraParam15->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam15_camera_Profile->setRowCount(16);
    tabWidget_CameraParam15_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam15_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam15_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>223&&i<240){
            tabWidget_CameraParam15_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C15[i%16]));
            tabWidget_CameraParam15_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam15_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam15_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam15_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam15_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam15);
    dialog_CameraParam15.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam16()
{
    dialog_CameraParam16.setWindowTitle(tr("CameraParam16配置"));
    dialog_CameraParam16.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam16 = new QTabWidget();
    tabWidget_CameraParam16->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam16->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam16_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam16_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam16_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam16_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam16->addTab(tab, QString());
    tabWidget_CameraParam16->setTabText(tabWidget_CameraParam16->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam16_camera_Profile->setRowCount(16);
    tabWidget_CameraParam16_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam16_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam16_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>239&&i<256){
            tabWidget_CameraParam16_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C16[i%16]));
            tabWidget_CameraParam16_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam16_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam16_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam16_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam16_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam16);
    dialog_CameraParam16.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam17()
{
    dialog_CameraParam17.setWindowTitle(tr("CameraParam17配置"));
    dialog_CameraParam17.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam17 = new QTabWidget();
    tabWidget_CameraParam17->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam17->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam17_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam17_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam17_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam17_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam17->addTab(tab, QString());
    tabWidget_CameraParam17->setTabText(tabWidget_CameraParam17->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam17_camera_Profile->setRowCount(16);
    tabWidget_CameraParam17_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam17_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam17_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>255&&i<272){
            tabWidget_CameraParam17_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C17[i%16]));
            tabWidget_CameraParam17_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam17_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam17_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam17_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam17_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam17);
    dialog_CameraParam17.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam18()
{
    dialog_CameraParam18.setWindowTitle(tr("CameraParam18配置"));
    dialog_CameraParam18.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam18 = new QTabWidget();
    tabWidget_CameraParam18->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam18->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam18_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam18_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam18_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam18_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam18->addTab(tab, QString());
    tabWidget_CameraParam18->setTabText(tabWidget_CameraParam18->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam18_camera_Profile->setRowCount(16);
    tabWidget_CameraParam18_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam18_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam18_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>271&&i<288){
            tabWidget_CameraParam18_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C18[i%16]));
            tabWidget_CameraParam18_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam18_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam18_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam18_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam18_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam18);
    dialog_CameraParam18.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam19()
{
    dialog_CameraParam19.setWindowTitle(tr("CameraParam19配置"));
    dialog_CameraParam19.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam19 = new QTabWidget();
    tabWidget_CameraParam19->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam19->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam19_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam19_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam19_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam19_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam19->addTab(tab, QString());
    tabWidget_CameraParam19->setTabText(tabWidget_CameraParam19->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam19_camera_Profile->setRowCount(16);
    tabWidget_CameraParam19_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam19_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam19_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>287&&i<304){
            tabWidget_CameraParam19_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C19[i%16]));
            tabWidget_CameraParam19_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam19_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam19_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam19_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam19_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam19);
    dialog_CameraParam19.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam20()
{
    dialog_CameraParam20.setWindowTitle(tr("CameraParam20配置"));
    dialog_CameraParam20.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam20 = new QTabWidget();
    tabWidget_CameraParam20->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam20->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam20_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam20_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam20_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam20_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam20->addTab(tab, QString());
    tabWidget_CameraParam20->setTabText(tabWidget_CameraParam20->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam20_camera_Profile->setRowCount(16);
    tabWidget_CameraParam20_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam20_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam20_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>303&&i<320){
            tabWidget_CameraParam20_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C20[i%16]));
            tabWidget_CameraParam20_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam20_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam20_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam20_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam20_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam20);
    dialog_CameraParam20.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam21()
{
    dialog_CameraParam21.setWindowTitle(tr("CameraParam21配置"));
    dialog_CameraParam21.setGeometry(QRect(1170, 123, 425, 614));
//-------------------------
    tabWidget_CameraParam21 = new QTabWidget();
    tabWidget_CameraParam21->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam21->setGeometry(QRect(0, 0, 400, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam21_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam21_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam21_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam21_camera_Profile->setGeometry(QRect(0, 0, 400, 614));
    tabWidget_CameraParam21->addTab(tab, QString());
    tabWidget_CameraParam21->setTabText(tabWidget_CameraParam21->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam21_camera_Profile->setRowCount(16);
    tabWidget_CameraParam21_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam21_camera_Profile->setColumnWidth(0,180);
    tabWidget_CameraParam21_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>319&&i<336){
            tabWidget_CameraParam21_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C21[i%16]));
            tabWidget_CameraParam21_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam21_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam21_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam21_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam21_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam21);
    dialog_CameraParam21.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam22()
{
    dialog_CameraParam22.setWindowTitle(tr("CameraParam22配置"));
    dialog_CameraParam22.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam22 = new QTabWidget();
    tabWidget_CameraParam22->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam22->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam22_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam22_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam22_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam22_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam22->addTab(tab, QString());
    tabWidget_CameraParam22->setTabText(tabWidget_CameraParam22->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam22_camera_Profile->setRowCount(16);
    tabWidget_CameraParam22_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam22_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam22_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>335&&i<352){
            tabWidget_CameraParam22_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C22[i%16]));
            tabWidget_CameraParam22_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam22_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam22_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam22_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam22_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam22);
    dialog_CameraParam22.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam23()
{
    dialog_CameraParam23.setWindowTitle(tr("CameraParam23配置"));
    dialog_CameraParam23.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam23 = new QTabWidget();
    tabWidget_CameraParam23->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam23->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam23_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam23_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam23_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam23_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam23->addTab(tab, QString());
    tabWidget_CameraParam23->setTabText(tabWidget_CameraParam23->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam23_camera_Profile->setRowCount(16);
    tabWidget_CameraParam23_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam23_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam23_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>351&&i<368){
            tabWidget_CameraParam23_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C23[i%16]));
            tabWidget_CameraParam23_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam23_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam23_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam23_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam23_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam23);
    dialog_CameraParam23.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam24()
{
    dialog_CameraParam24.setWindowTitle(tr("CameraParam24配置"));
    dialog_CameraParam24.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam24 = new QTabWidget();
    tabWidget_CameraParam24->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam24->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam24_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam24_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam24_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam24_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam24->addTab(tab, QString());
    tabWidget_CameraParam24->setTabText(tabWidget_CameraParam24->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam24_camera_Profile->setRowCount(16);
    tabWidget_CameraParam24_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam24_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam24_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>367&&i<384){
            tabWidget_CameraParam24_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C24[i%16]));
            tabWidget_CameraParam24_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam24_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam24_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam24_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam24_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam24);
    dialog_CameraParam24.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam25()
{
    dialog_CameraParam25.setWindowTitle(tr("CameraParam25配置"));
    dialog_CameraParam25.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam25 = new QTabWidget();
    tabWidget_CameraParam25->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam25->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam25_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam25_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam25_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam25_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam25->addTab(tab, QString());
    tabWidget_CameraParam25->setTabText(tabWidget_CameraParam25->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam25_camera_Profile->setRowCount(16);
    tabWidget_CameraParam25_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam25_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam25_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>383&&i<400){
            tabWidget_CameraParam25_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C25[i%16]));
            tabWidget_CameraParam25_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam25_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam25_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam25_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam25_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam25);
    dialog_CameraParam25.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam26()
{
    dialog_CameraParam26.setWindowTitle(tr("CameraParam26配置"));
    dialog_CameraParam26.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam26 = new QTabWidget();
    tabWidget_CameraParam26->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam26->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam26_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam26_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam26_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam26_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam26->addTab(tab, QString());
    tabWidget_CameraParam26->setTabText(tabWidget_CameraParam26->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam26_camera_Profile->setRowCount(16);
    tabWidget_CameraParam26_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam26_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam26_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>399&&i<416){
            tabWidget_CameraParam26_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C26[i%16]));
            tabWidget_CameraParam26_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam26_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam26_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam26_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam26_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam26);
    dialog_CameraParam26.setLayout(vlayout);
}

void Dialog::init_dialog_CameraParam27()
{
    dialog_CameraParam27.setWindowTitle(tr("CameraParam27配置"));
    dialog_CameraParam27.setGeometry(QRect(1170, 123, 275, 614));
//-------------------------
    tabWidget_CameraParam27 = new QTabWidget();
    tabWidget_CameraParam27->setObjectName(QStringLiteral("tabWidget"));
    tabWidget_CameraParam27->setGeometry(QRect(0, 0, 250, 614));
    QWidget *tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    tabWidget_CameraParam27_camera_Profile = new QTableWidget(tab);
    tabWidget_CameraParam27_camera_Profile->horizontalHeader()->setStretchLastSection(true);
    tabWidget_CameraParam27_camera_Profile->setObjectName(QStringLiteral("tableWidget_Profile"));
    tabWidget_CameraParam27_camera_Profile->setGeometry(QRect(0, 0, 250, 614));
    tabWidget_CameraParam27->addTab(tab, QString());
    tabWidget_CameraParam27->setTabText(tabWidget_CameraParam27->indexOf(tab), QApplication::translate("Dialog", "tableWidget_camera_Profile", Q_NULLPTR));
    /*-------------------------*/
    tabWidget_CameraParam27_camera_Profile->setRowCount(16);
    tabWidget_CameraParam27_camera_Profile->setColumnCount(2);
    tabWidget_CameraParam27_camera_Profile->setColumnWidth(0,120);
    tabWidget_CameraParam27_camera_Profile->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值")<<tr("命令"));//设置水平方向的表头
    load_config_flag = 1;
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
            if(i>415&&i<432){
            tabWidget_CameraParam27_camera_Profile->setItem(i%16,0, new QTableWidgetItem(string_C27[i%16]));
            tabWidget_CameraParam27_camera_Profile->setItem(i%16,1, new QTableWidgetItem(str.section(':', 1, 1).trimmed()));
            }
            i++;
        }
    }
    load_config_flag = 0;
/*****************************************************************************/
    connect(tabWidget_CameraParam27_camera_Profile,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam27_camera_Profile_itemChanged(QTableWidgetItem*)));
    connect(tabWidget_CameraParam27_camera_Profile,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(on_tabWidget_CameraParam27_camera_Profile_itemActivated(QTableWidgetItem*)));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabWidget_CameraParam27);
    dialog_CameraParam27.setLayout(vlayout);
}



