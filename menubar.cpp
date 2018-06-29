#include "dialog.h"

void Dialog::init_menu()
{
    menuBar = new QMenuBar(this);
    menu[0] = new QMenu("系统");
    QAction* pActionA = new QAction("串口设置");
    menu[0]->addAction(pActionA);
    QAction* pActionC = new QAction("网络设置");
    menu[0]->addAction(pActionC);
    act[0] = new QAction("退出",this);
    act[0]->setShortcut(Qt::CTRL | Qt::Key_O );
    menu[0]->addAction(act[0]);

    menu[1] = new QMenu("配置");
    menuc =new QMenu("打开配置");
    menu[1]->addMenu(menuc);
    QAction* pActionsc = new QAction("用户配置");
    menuc->addAction(pActionsc);
    QAction* pActionp = new QAction("程序员配置");
    menuc->addAction(pActionp);

    QAction* pActionF = new QAction("关闭配置窗口");
    menu[1]->addAction(pActionF);
    QAction* pActionB = new QAction("保存配置");
    menu[1]->addAction(pActionB);
    QAction* pActionD = new QAction("加载配置");
    menu[1]->addAction(pActionD);

    menu[2] = new QMenu("工具");
    QAction* pActionG = new QAction("手柄");
    menu[2]->addAction(pActionG);
    //menu[2]->addAction("测试高速球");

    QObject::connect(pActionA, SIGNAL(triggered(bool)), this, SLOT(onMsg()));
    QObject::connect(pActionB, SIGNAL(triggered(bool)), this, SLOT(onMsgB()));
    QObject::connect(pActionC, SIGNAL(triggered(bool)), this, SLOT(onMsgC()));
    QObject::connect(pActionD, SIGNAL(triggered(bool)), this, SLOT(onMsgD()));
    QObject::connect(act[0], SIGNAL(triggered(bool)), this, SLOT(onMsgE()));
    QObject::connect(pActionF, SIGNAL(triggered(bool)), this, SLOT(onMsgF()));
    QObject::connect(pActionG, SIGNAL(triggered(bool)), this, SLOT(onMsgG()));
    QObject::connect(pActionsc, SIGNAL(triggered(bool)), this, SLOT(onMsgsc()));
    QObject::connect(pActionp, SIGNAL(triggered(bool)), this, SLOT(onMesgp()));

    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[1]);
    menuBar->addMenu(menu[2]);
    menuBar->setGeometry(0,0,this->width(),25);
}
