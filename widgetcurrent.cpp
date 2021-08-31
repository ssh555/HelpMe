#include "widgetcurrent.h"
#include "ui_widgetcurrent.h"
#include "serialreceiver.h"
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include "patient.h"
WidgetCurrent::WidgetCurrent( QString comSender, QString comReceiver,QString name, QString date, QString pic_str, int age, int number, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::WidgetCurrent)
{
    //主UI设计
    ui->setupUi(this);
    this->setStyleSheet("background-color: black");
    this->setWindowFlag( Qt::FramelessWindowHint );

    //UI对应信息显示
    QImage *img = new QImage();
    img->load(pic_str);
    ui->photo->setPixmap( QPixmap::fromImage(*img));
    ui->photo->setScaledContents(true);
    ui->photo->resize( ui->photo->width(), ui->photo->height());
    ui->name->setText( name );
    ui->date->setText( date );
    ui->age->setText( QString::number(age, 10) );
    ui->number->setText( QString::number(number, 10) );

    //发送和接受串口
    sender = new SerialSender( comSender, nullptr );
    receiver = new SerialReceiver( comReceiver, nullptr );//接收数据用的串口
    connect( receiver, &SerialReceiver::Signal_ECG_Received, this, &WidgetCurrent::Slot_Draw_Wave );//每秒实时波形数据
    connect( receiver, &SerialReceiver::Signal_BPM_Received, this, &WidgetCurrent::Slot_Show_Data );//每分钟心率

    //对应三个波形ECG、SpO2、RESP
    drawECG = new DrawWave( ui->ECGWave, QColor("#7FFF00"), QColor("#808080") );//绘制波形
    showECG = new ShowData( ui->ECGData, "#7FFF00", "#808080" );//实时数值
    connect( this, &WidgetCurrent::Signal_Draw_1, drawECG, &DrawWave::Slot_Data_Handle );//绘制波形信号DrawWave
    connect( this, &WidgetCurrent::Signal_Show_1, showECG, &ShowData::Slot_Data_Handle);//显示数据信号ShowData

    drawSpO2 = new DrawWave( ui->SpO2Wave, QColor("#FFFF00"), QColor("#778899") );
    showSpO2 = new ShowData( ui->SpO2Data, "#FFFF00", "#778899" );
    connect( this, &WidgetCurrent::Signal_Draw_2, drawSpO2, &DrawWave::Slot_Data_Handle );
    connect( this, &WidgetCurrent::Signal_Show_2, showSpO2, &ShowData::Slot_Data_Handle );

    drawRESP = new DrawWave( ui->RESPWave, QColor("#7FFF00"), QColor("#808080") );
    showRESP = new ShowData( ui->RESPData, "#7FFF00", "#808080" );
    connect( this, &WidgetCurrent::Signal_Draw_3, drawRESP, &DrawWave::Slot_Data_Handle );
    connect( this, &WidgetCurrent::Signal_Show_3, showRESP, &ShowData::Slot_Data_Handle );

    //右上角时钟
    LCDClock_Display( this );

    //对应历史界面
    widgetHistory = new WidgetHistory( );
    connect( widgetHistory, &WidgetHistory::Signal_History_To_Current, this, &WidgetCurrent::Slot_History_To_Current);//进入历史界面

}

WidgetCurrent::~WidgetCurrent()
{
    delete ui;
}

void WidgetCurrent::LCDClock_Display(QWidget *widget)//时钟显示
{
    QTimer *timer = new QTimer( widget );
    timer->start( 1000 );
    connect( timer, &QTimer::timeout, this, &WidgetCurrent::LCDClock_Refresh );

}

void WidgetCurrent::LCDClock_Refresh()//时钟更新
{
    QDateTime dataTime = QDateTime::currentDateTime();
    ui->dateClock->setDigitCount(10);
    ui->dateClock->display( dataTime.toString( "yyyy-MM-dd" ) );
    ui->timeClock->setDigitCount(8);
    ui->timeClock->display( dataTime.toString( "hh:mm:ss" ));
}


void WidgetCurrent::Slot_History_To_Current()//历史界面到当前界面
{
    widgetHistory->hide();
    this->show();
}


void WidgetCurrent::Slot_Draw_Wave( int data1, int data2, int data3 )//从串口接受波形发送给波形绘制函数DrawWave
{
    emit Signal_Draw_1( data1 );
    emit Signal_Draw_2( data2 );
    emit Signal_Draw_3( data3 );
}

void WidgetCurrent::Slot_Show_Data( int data1, int data2, int data3 )//从串口接受数值发送给数值显示函数ShowData
{
    emit Signal_Show_1( data1 );
    emit Signal_Show_2( data2 );
    emit Signal_Show_3( data3 );
}


void WidgetCurrent::on_backButton_clicked()//返回按钮
{
    emit Signal_Current_To_Select();
}


void WidgetCurrent::on_historyButton_clicked()//历史界面按钮
{
    this->hide();
    widgetHistory->show();
}
