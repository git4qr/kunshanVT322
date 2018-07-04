#include "dialog.h"

#define PI 3.14159269798

//int set_config_count = 0;
int get_config_count = 0;

void Dialog::onMsgsc()
{
    dialog_SerialParam.show();
}
void Dialog::onMesgp()
{
    emit toProgrammer();
}
void Dialog::receivePlatConfig()
{
    dialog_config.show();
}

void Dialog::receivePID()
{
    dialog_pid.show();
}

void Dialog::receiveJoshandle()
{
    dialog_JosHandle.show();
}

void Dialog::receiveJosMap1()
{
    dialog_Josmap1.show();
}

void Dialog::receiceJosMap2()
{
    dialog_Josmap2.show();
}

void Dialog::receiceKeyboardMap1()
{
    dialog_Keyboardmap1.show();
}

void Dialog::receiveKeyboardMap2()
{
    dialog_Keyboardmap2.show();
}

void Dialog::receiveUTC1()
{
    dialog_UTCParam1.show();
}

void Dialog::receiveUTC2()
{
    dialog_UTCParam2.show();
}

void Dialog::receiveUTC3()
{
    dialog_UTCParam3.show();
}

void Dialog::receiveSerial()
{
    dialog_SerialParam.show();
}

void Dialog::receiveEM()
{
    dialog_EMParam.show();
}

void Dialog::receiveOSD1()
{
    dialog_OSDParam1.show();
}

void Dialog::receiveOSD2()
{
    dialog_OSDParam2.show();
}

void Dialog::receiveOSD3()
{
    dialog_OSDParam3.show();
}

void Dialog::receiveCamera1()
{
    dialog_CameraParam1.show();
}

void Dialog::receiveCamera2()
{
    dialog_CameraParam2.show();
}

void Dialog::receiveCamera3()
{
    dialog_CameraParam3.show();
}

void Dialog::receiveCamera4()
{
    dialog_CameraParam4.show();
}

void Dialog::receiveCamera5()
{
    dialog_CameraParam5.show();
}

void Dialog::receiveCamera6()
{
    dialog_CameraParam6.show();
}

void Dialog::receiveCamera7()
{
    dialog_CameraParam7.show();
}

void Dialog::receiveCamera8()
{
    dialog_CameraParam8.show();
}

void Dialog::receiveCamera9()
{
    dialog_CameraParam9.show();
}

void Dialog::receiveCamera10()
{
    dialog_CameraParam10.show();
}

void Dialog::receiveCamera11()
{
    dialog_CameraParam11.show();
}

void Dialog::receiveCamera12()
{
    dialog_CameraParam12.show();
}

void Dialog::receiveCamera13()
{
    dialog_CameraParam13.show();
}

void Dialog::receiveCamera14()
{
    dialog_CameraParam14.show();
}

void Dialog::receiveCamera15()
{
    dialog_CameraParam15.show();
}

void Dialog::receiveCamera16()
{
    dialog_CameraParam16.show();
}

void Dialog::receiveCamera17()
{
    dialog_CameraParam17.show();
}

void Dialog::receiveCamera18()
{
    dialog_CameraParam18.show();
}

void Dialog::receiveCamera19()
{
    dialog_CameraParam19.show();
}

void Dialog::receiveCamera20()
{
    dialog_CameraParam20.show();
}

void Dialog::receiveCamera21()
{
    dialog_CameraParam21.show();
}

void Dialog::receiveCamera22()
{
    dialog_CameraParam22.show();
}

void Dialog::receiveCamera23()
{
    dialog_CameraParam23.show();
}

void Dialog::receiveCamera24()
{
    dialog_CameraParam24.show();
}

void Dialog::receiveCamera25()
{
    dialog_CameraParam25.show();
}

void Dialog::receiveCamera26()
{
    dialog_CameraParam26.show();
}

void Dialog::receiveCamera27()
{
    dialog_CameraParam27.show();
}

void Dialog::on_tableWidget_Profile_itemChanged(QTableWidgetItem *item)
{
#if 0
    set_config_count++;
    if(set_config_count<1345)
    {
    }
    else
    {
#endif
        if(load_config_flag)
            return;
        if(1 == item->column())
        {
            int i = tableWidget_Profile->currentItem()->row();
            int block = 1;
            int field = i%16;
            float value = item->text().toFloat();
            if(2 == i)
            {
                value = (1/(value*PI/180*5.0*9/PI));
                QString strx = QString("%1").arg(value);
                load_config_flag = 1;
                tableWidget_Profile->item(2,1)->setText(strx);
                load_config_flag = 0;
                //ui->label_scalarx->setText(strx);
            }
            else if(3 == i)
            {
                value = (1/(value*PI/180*4.5*9/PI));
                load_config_flag = 1;
                tableWidget_Profile->item(3,1)->setText(QString("%1").arg(value));
                load_config_flag = 0;
                //ui->label_scalary->setText(QString("%1").arg(value));
            }
            send_mutex.lock();
            send_arr[3] = 0x30;
            send_arr[4] = block;
            send_arr[5] = field;
            memcpy(send_arr+6,&value,4);
            send_oneframe(11);
            send_mutex.unlock();

        }
    //}
}


void Dialog::on_tableWidget_Profile_itemActivated(QTableWidgetItem *item)
{
        get_config_count++;
        if(0 == item->column())
        {
            int i =tableWidget_Profile->currentItem()->row();
            int gblock = 1;
            int gfield = i%16;
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
}

void Dialog::on_tabwidget_pid_Profile_itemChanged(QTableWidgetItem *item)
{

        if(load_config_flag)
            return;
        if(1 == item->column())
        {
            int i = tabwidget_pid_Profile->currentItem()->row();
            //qDebug()<<"i:"<<i<<endl;
            int block = 2;
            int field = i%16;
            float value = item->text().toFloat();

            send_mutex.lock();
            send_arr[3] = 0x30;
            send_arr[4] = block;
            send_arr[5] = field;
            memcpy(send_arr+6,&value,4);
            send_oneframe(11);
            send_mutex.unlock();

        }
}

void Dialog::on_tabwidget_pid_Profile_itemActivated(QTableWidgetItem *item)
{
    get_config_count++;
    if(0 == item->column())
    {
        int i = tabwidget_pid_Profile->currentItem()->row();
        int gblock = 2;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_JosHandle_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_JosHandle_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 3;
        int field = i%16;
        float value = item->text().toFloat();


        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_JosHandle_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_JosHandle_Profile->currentItem()->row();
        int gblock = 3;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_Josmap1_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_Josmap1_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 4;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_Josmap1_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_Josmap1_Profile->currentItem()->row();
        int gblock = 4;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_Josmap2_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_Josmap2_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 5;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_Josmap2_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_Josmap2_Profile->currentItem()->row();
        int gblock = 5;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_Keyboardmap1_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_Keyboardmap1_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 6;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_Keyboardmap1_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_Keyboardmap1_Profile->currentItem()->row();
        int gblock = 6;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_Keyboardmap2_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_Keyboardmap2_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 7;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_Keyboardmap2_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_Keyboardmap2_Profile->currentItem()->row();
        int gblock =7;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_SerialParam_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_SerialParam_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 8;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_SerialParam_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_SerialParam_Profile->currentItem()->row();
        int gblock = 8;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_UTCParam1_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_UTCParam1_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 9;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_UTCParam1_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_UTCParam1_Profile->currentItem()->row();
        int gblock = 9;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_UTCParam3_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_UTCParam3_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 11;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_UTCParam3_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_UTCParam3_Profile->currentItem()->row();
        int gblock = 11;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_UTCParam2_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_UTCParam2_Profile->currentItem()->row();
        //qDebug()<<"i:"<<i<<endl;
        int block = 10;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_UTCParam2_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_UTCParam2_Profile->currentItem()->row();
        int gblock = 10;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_EMParam_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_EMParam_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 12;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_EMParam_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_EMParam_Profile->currentRow();
        int gblock = 12;
        //qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_OSDParam1_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_OSDParam1_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 13;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_OSDParam1_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_OSDParam1_Profile->currentRow();
        int gblock = 13;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_OSDParam2_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_OSDParam2_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 14;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_OSDParam2_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_OSDParam2_Profile->currentRow();
        int gblock = 14;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_OSDParam3_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_OSDParam3_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 15;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_OSDParam3_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_OSDParam3_Profile->currentRow();
        int gblock = 15;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam1_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam1_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 16;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam1_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam1_camera_Profile->currentRow();
        int gblock = 16;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam2_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam2_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 17;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam2_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam2_camera_Profile->currentRow();
        int gblock = 17;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam3_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam3_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 18;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam3_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam3_camera_Profile->currentRow();
        int gblock =18;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam4_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam4_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 19;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam4_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam4_camera_Profile->currentRow();
        int gblock = 19;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam5_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam5_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 20;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam5_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam5_camera_Profile->currentRow();
        int gblock = 20;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam6_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam6_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 21;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam6_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam6_camera_Profile->currentRow();
        int gblock = 21;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam7_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam7_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 22;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam7_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam7_camera_Profile->currentRow();
        int gblock = 22;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam8_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam8_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 23;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam8_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam8_camera_Profile->currentRow();
        int gblock = 23;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam9_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam9_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 24;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam9_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam9_camera_Profile->currentRow();
        int gblock = 24;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam10_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam10_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 25;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam10_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam10_camera_Profile->currentRow();
        int gblock = 25;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam11_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam11_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 26;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam11_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam11_camera_Profile->currentRow();
        int gblock = 26;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam12_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam12_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 27;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam12_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam12_camera_Profile->currentRow();
        int gblock = 27;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam13_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam13_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 28;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam13_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam13_camera_Profile->currentRow();
        int gblock = 28;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam14_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam14_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 29;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam14_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam14_camera_Profile->currentRow();
        int gblock = 29;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam15_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam15_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 30;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam15_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam15_camera_Profile->currentRow();
        int gblock = 30;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam16_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam16_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 31;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam16_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam16_camera_Profile->currentRow();
        int gblock = 31;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam17_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam17_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 32;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam17_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam17_camera_Profile->currentRow();
        int gblock = 32;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam18_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam18_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 33;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam18_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam18_camera_Profile->currentRow();
        int gblock = 33;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam19_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam19_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 34;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam19_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam19_camera_Profile->currentRow();
        int gblock = 34;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam20_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam20_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 35;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam20_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam20_camera_Profile->currentRow();
        int gblock = 35;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam21_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam21_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 36;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam21_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam21_camera_Profile->currentRow();
        int gblock = 36;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam22_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam22_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 37;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam22_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam22_camera_Profile->currentRow();
        int gblock = 37;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam23_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam23_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 38;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam23_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam23_camera_Profile->currentRow();
        int gblock = 38;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam24_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam24_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 39;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam24_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam24_camera_Profile->currentRow();
        int gblock = 39;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam25_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam25_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 40;
        int field = i%16;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam25_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam25_camera_Profile->currentRow();
        int gblock = 40;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
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
}

void Dialog::on_tabWidget_CameraParam26_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam26_camera_Profile->currentRow();
        qDebug()<<"i:"<<i<<endl;
        int block = 41;
        int field = i%16;

        qDebug()<<"field"<<field<<endl;
        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam26_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam26_camera_Profile->currentRow();
        int gblock = 41;

        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;

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
}

void Dialog::on_tabWidget_CameraParam27_camera_Profile_itemChanged(QTableWidgetItem *item)
{
    if(load_config_flag)
        return;
    if(1 == item->column())
    {
        int i = tabWidget_CameraParam27_camera_Profile->currentRow();
        //qDebug()<<"i:"<<i<<endl;
        int block = 42;
        int field = i%16;

        float value = item->text().toFloat();

        send_mutex.lock();
        send_arr[3] = 0x30;
        send_arr[4] = block;
        send_arr[5] = field;
        memcpy(send_arr+6,&value,4);
        send_oneframe(11);
        send_mutex.unlock();

    }
}

void Dialog::on_tabWidget_CameraParam27_camera_Profile_itemActivated(QTableWidgetItem *item)
{
    if(0 == item->column())
    {
        int i = tabWidget_CameraParam27_camera_Profile->currentRow();
        int gblock = 42;
        qDebug()<<"gblock"<<gblock<<endl;
        int gfield = i%16;
         qDebug()<<"gfield"<<gfield<<endl;
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
}
