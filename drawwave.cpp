#include "drawwave.h"
#include "widgetcurrent.h"
#include "showdata.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
DrawWave::DrawWave(QWidget *parent, QColor color1, QColor color2) : QWidget(parent)
{
    this->resize(529,136);
    //定时器，触发QTimerEvent
    basicTimer = new QBasicTimer();
    basicTimer->start( 100, this );

    //存储画笔和背景颜色
    penColor = color1;
    backgroundColor = color2;
    //parent->setStyleSheet("background-color:"+backgroundColor.name());

    //绘制点坐标初始化
    currentX = 0;
    currentY = 0;
    lastX = 0;
    lastY = 0;

    //绘图设备Pixmap，背景透明
    pixmap = new QPixmap( 529, 136 );//画布
    pixmap->fill( backgroundColor );//填充对应背景色

}

void DrawWave::Slot_Data_Handle( int data )//接收数据并处理的槽函数，同时发送信号
{
    //将波形绘制在pixmap上
    this->Draw_Wave_To_Pixmap( data );//传递数据
    basicTimer->start(100, this);//
    this->update();//触发QPaintEvent

}

void DrawWave::timerEvent( QTimerEvent *timerEvent )
{
    this->Draw_Wave_To_Pixmap( 2048 );//没有接受信号时为x轴平行线，数值为2048
    this->update();//触发QPaintEvent
}

void DrawWave::paintEvent( QPaintEvent *paintEvent )
{
    QPainter *painter = new QPainter();
    painter->begin( this );
    painter->resetTransform();
    painter->drawPixmap( 0, 0, *pixmap );
    painter->resetTransform();
    painter->end();
}

void DrawWave::Draw_Wave_To_Pixmap( int data )
{

    //接收数据，更新存储的点坐标
    int height = this->height();
    int width = this->width();
//    qDebug()<<"lastX1 " + QString::number(lastX);
//    qDebug()<<"lastY1 " + QString::number(lastY);
//    qDebug()<<"currentX1 " + QString::number(currentX);
//    qDebug()<<"currentY1 " + QString::number(currentY);

    lastX = currentX;//当前X和Y赋值给last存储
    lastY = currentY;
    currentX = lastX + 1;
    if ( currentX > width )//横坐标超过边界归零
    {
        currentX = 0;
        lastX=0;
    }
    currentY = round( height / 2.00 - ( ( data - 2048 ) / 600.00 ) * height / 2.00 );//注意doubel型转换

//    qDebug()<<"data" + QString::number(data);
//    qDebug()<<"currentY" + QString::number(currentY);
//    qDebug()<<"height" + QString::number(height);
//    qDebug()<<"lastX2 " + QString::number(lastX);
//    qDebug()<<"lastY2 " + QString::number(lastY);
//    qDebug()<<"currentX2 " + QString::number(currentX);
//    qDebug()<<"currentY2 " + QString::number(currentY);

    //绘制波形在pixmap
    QPainter *painter = new QPainter();
    painter->begin( pixmap );
    this->Draw_Wave( painter );
    painter->end();
}

void DrawWave::Draw_Wave( QPainter *painter )
{

    QPen *pen = new QPen();
    pen->setWidth( 2 );
    pen->setColor( QColor( penColor) );
    //根据pen属性为painter设置画笔
    painter->setPen( *pen );

    //获取当前窗口宽
    int height = this->height();

//    擦除当前列波形
    painter->save();
    pen->setColor( QColor( backgroundColor) );
    painter->setPen( *pen );
    pen->setWidth( 2 );
    painter->drawLine( currentX, 0, currentX , height );
    painter->restore();//还原当前配置
    //画线的起止点
    QPoint *lineBegin = new QPoint();
    QPoint *lineEnd = new QPoint();

    //设定本次直线起止点
    lineBegin->setX( lastX );
    lineBegin->setY( lastY );
    lineEnd->setX( currentX );
    lineEnd->setY( currentY );
//    qDebug()<<"Draw_Wave";

//    qDebug()<<"lastX3 " + QString::number(lastX);
//    qDebug()<<"lastY3 " + QString::number(lastY);
//    qDebug()<<"currentX3 " + QString::number(currentX);
//    qDebug()<<"currentY3 " + QString::number(currentY);
//    qDebug()<<lineBegin->x();
//    qDebug()<<lineBegin->y();
//    qDebug()<<lineEnd->x();
//    qDebug()<<lineEnd->y();

    //画线
    painter->drawLine( *lineBegin, *lineEnd );
}
