#ifndef WIDGETHISTORY_H
#define WIDGETHISTORY_H

#include "drawwave.h"
#include "showdata.h"
#include "serialreceiver.h"
#include "serialsender.h"
#include <QWidget>

namespace Ui {
class WidgetHistory;
}

class WidgetHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetHistory( QString comSender = "COM21", QString comReceiver = "COM22", QString name = "name", QString date = "date", QString pic_str = ":/picture/P1.jpg", int age = 10, int number = 1, QWidget *parent = nullptr );
    ~WidgetHistory();
    DrawWave *drawECG;
    DrawWave *drawSpO2;
    DrawWave *drawRESP;
    ShowData *showECG;
    ShowData *showSpO2;
    ShowData *showRESP;

    WidgetHistory *widgetHistory;
    SerialReceiver *receiver;
    SerialSender *sender;

private slots:
    void on_backButton_clicked();
    void Slot_Draw_Wave( int data1, int data2, int data3 );
    void Slot_Show_Data( int data1, int data2, int data3 );

private:
    Ui::WidgetHistory *ui;

signals:
    void Signal_Draw_1( int data1 );
    void Signal_Draw_2( int data2 );
    void Signal_Draw_3( int data3 );
    void Signal_Show_1( int data1 );
    void Signal_Show_2( int data2 );
    void Signal_Show_3( int data3 );
    void Signal_History_To_Current();

};

#endif // WIDGETHISTORY_H
