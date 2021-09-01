#include "widgethistory.h"
#include "ui_widgethistory.h"
#include "drawwave.h"
#include "showdata.h"
#include "serialreceiver.h"
#include "serialsender.h"

WidgetHistory::WidgetHistory( QString comSender, QString comReceiver,QString name, QString date, QString pic_str, int age, int number, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::WidgetHistory)
{
    /*需要绘制波形和数值时，让此WidgetHistory发送Signal_Draw_1（波形）、Signal_Show_1（数值）等*/

    ui->setupUi(this);
    this->setStyleSheet("background-color: black");
    this->setWindowFlag( Qt::FramelessWindowHint );

    //患者照片
    QImage *img = new QImage();
    img->load(pic_str);
    ui->photo->setPixmap( QPixmap::fromImage(*img));
    ui->photo->setScaledContents(true);
    ui->photo->resize( ui->photo->width(), ui->photo->height());
    ui->name->setText( name );
    ui->date->setText( date );
    ui->age->setText( QString::number(age, 10) );
    ui->number->setText( QString::number(number, 10) );

//    //串口
//    sender = new SerialSender( comSender, nullptr );
//    receiver = new SerialReceiver( comReceiver, nullptr );//接收数据用的串口

    drawECG = new DrawWave( ui->ECGWave, QColor("#7FFF00"), QColor("#808080") );
    showECG = new ShowData( ui->ECGData, "#7FFF00", "#808080" );
    connect( this, &WidgetHistory::Signal_Draw_1, drawECG, &DrawWave::Slot_Data_Handle );//绘制波形信号DrawWave
    connect( this, &WidgetHistory::Signal_Show_1, showECG, &ShowData::Slot_Data_Handle);//显示数据信号ShowData

    drawSpO2 = new DrawWave( ui->SpO2Wave, QColor("#FFFF00"), QColor("#778899") );
    showSpO2 = new ShowData( ui->SpO2Data, "#FFFF00", "#778899" );
    connect( this, &WidgetHistory::Signal_Draw_2, drawSpO2, &DrawWave::Slot_Data_Handle );
    connect( this, &WidgetHistory::Signal_Show_2, showSpO2, &ShowData::Slot_Data_Handle );

    drawRESP = new DrawWave( ui->RESPWave, QColor("#7FFF00"), QColor("#808080") );
    showRESP = new ShowData( ui->RESPData, "#7FFF00", "#808080" );
    connect( this, &WidgetHistory::Signal_Draw_3, drawRESP, &DrawWave::Slot_Data_Handle );
    connect( this, &WidgetHistory::Signal_Show_3, showRESP, &ShowData::Slot_Data_Handle );
}

WidgetHistory::~WidgetHistory()
{
    delete ui;
}

void WidgetHistory::on_backButton_clicked()//返回按钮
{
    emit Signal_History_To_Current();
}

void WidgetHistory::Slot_Draw_Wave( int data1, int data2, int data3 )//从？？？接受波形发送给波形绘制函数DrawWave
{
    emit Signal_Draw_1( data1 );
    emit Signal_Draw_2( data2 );
    emit Signal_Draw_3( data3 );
}

void WidgetHistory::Slot_Show_Data( int data1, int data2, int data3 )//从？？？接受数值发送给数值显示函数ShowData
{
    emit Signal_Show_1( data1 );
    emit Signal_Show_2( data2 );
    emit Signal_Show_3( data3 );
}


