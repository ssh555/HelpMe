#ifndef SERIALRECEIVER_H
#define SERIALRECEIVER_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>

class SerialReceiver : public QWidget
{
    Q_OBJECT
public:
    explicit SerialReceiver(QWidget *parent = nullptr);
    explicit SerialReceiver(const QString &comName, QWidget *parent = nullptr);
//private:
    QSerialPort *com;
    QString serialportName = "COM2"; //串口号默认COM2

    char status = 0;
    char pkgHead;
    char pkgDataHead;
    char pkgDataBuf[10];
    char pkgData[10];
    char pkgCrc;
    int  pkgDataCnt;
    int ecg1, ecg2, ecg3;   //心电图y轴数据

    // 计算心率相关变量
    int ecg2PulseMax;
    int ecg2PulseMid;
    int ecg2Zero = 2048; // 无信号输入时输出结果为2048
    int ecg2Buff[2000]; //采样率为500=每秒钟采样500次，假设心率很慢2s一次，一个周期有1000个数据，这里取2000个
    unsigned int ecg2BuffIndex = 0;
    char prePulse;
    char pulse;
    long long pulseStart = 0, pulseEnd = 0;
    int ecg2Period;
    int ecg2Bpm = 75;    //心率

    int Serial_Init(void);
    void Serial_Rx(void);
    void RxData_Handle(char data);
    void ECG_BPM_Calc(int ecgData);
    int Get_Max(int * data, int len);

signals:
    void Signal_ECG_Received(int ecg1, int ecg2, int ecg3);     //波形y轴数据
    void Signal_BPM_Received(int bpm1, int bmp2, int bmp3);     //心率数据

};

#endif // SERIALRECEIVER_H
