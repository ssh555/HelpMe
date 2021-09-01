#ifndef WIDGETCURRENT_H
#define WIDGETCURRENT_H

#include "drawwave.h"
#include "showdata.h"
#include "serialreceiver.h"
#include "serialsender.h"
#include "widgethistory.h"
#include "patientform.h"
#include <QWidget>

namespace Ui {
class WidgetCurrent;
}

class WidgetCurrent : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCurrent( QString comSender = "COM1", QString comReceiver = "COM2", QString name = "name", QString date = "date", QString pic_str = ":/picture/P1.jpg", int age = 10, int number = 1, QWidget *parent = nullptr );
    ~WidgetCurrent();
    void LCDClock_Display( QWidget *widget );
    void LCDClock_Refresh();

    DrawWave *drawECG;
    DrawWave *drawSpO2;
    DrawWave *drawRESP;
    ShowData *showECG;
    ShowData *showSpO2;
    ShowData *showRESP;

    WidgetHistory *widgetHistory;

    SerialReceiver *receiver;
    SerialSender *sender;

private:
    Ui::WidgetCurrent *ui;

private slots:
    void Slot_History_To_Current();
    void Slot_Draw_Wave( int data1, int data2, int data3 );
    void Slot_Show_Data( int data1, int data2, int data3 );
    void on_backButton_clicked();
    void on_historyButton_clicked();

signals:
    void Signal_Draw_1( int data1 );
    void Signal_Draw_2( int data2 );
    void Signal_Draw_3( int data3 );
    void Signal_Show_1( int data1 );
    void Signal_Show_2( int data2 );
    void Signal_Show_3( int data3 );
    void Signal_Current_To_Select();
};

#endif // WIDGETCURRENT_H
