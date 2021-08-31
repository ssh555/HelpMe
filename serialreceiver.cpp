#include "serialreceiver.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QDateTime>

SerialReceiver::SerialReceiver(QWidget *parent) : QWidget(parent)
{
    ecg2Bpm = 75;
    this->status=-1;
    if( 0 != this->Serial_Init() ){
        qDebug() << "Receiver: serialInit error!";
        return;
    }
}

SerialReceiver::SerialReceiver(const QString &comName, QWidget *parent) : QWidget(parent)
{
    ecg2Bpm = 75;
    this->status=-1;
    serialportName = comName;
    if( 0 != this->Serial_Init() ){
        qDebug() << "Receiver: serialInit error!";
        return;
    }
}

int SerialReceiver::Serial_Init(void)
{
    // 打印串口信息
    // foreach: 标准C++中没有这个关键字
    // qt自己实现了这个关键字，如下会便利availablePorts，并把每个结果依次赋值给info，有点像for
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
    }//执行完应该在应用程序输出位置看到串口数据，需要先启动串口模拟器，并创建串口

    // 创建串口对象, 在头文件中定义了指针
    com = new QSerialPort();
    // 配置串口号
    com->setPortName(this->serialportName);
    // 尝试打开串口
    if(!com->open(QIODevice::ReadWrite))
    {
        qDebug() << "serial open err: " << this->serialportName;
        return -1;
    }
    else
        qDebug()<<"serial open success:"<<com->portName();

    // 配置串口参数
    // 波特率=115200, 每秒钟发送115200个bit，方向=双向均采用这个波特率
    com->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    // 数据位
    com->setDataBits(QSerialPort::Data8);
    // 流控=无
    com->setFlowControl(QSerialPort::NoFlowControl);
    // 校验位=无
    com->setParity(QSerialPort::NoParity);
    // 停止位=1
    com->setStopBits(QSerialPort::OneStop);

    // 关联信号与槽函数
    // 当串口发出"可读"信号时，执行serialRx函数
    connect(com, &QSerialPort::readyRead, this, &SerialReceiver::Serial_Rx);
    return 0;
}

void SerialReceiver::Serial_Rx()
{
    QByteArray data = 0;

    // 读串口数据并处理
    while (!com->atEnd())
    {
        QByteArray data = this->com->read(1);
        this->RxData_Handle(data[0]);
        if (this->status == 4)
        {
            // 发送信号画波形
            emit Signal_ECG_Received( ecg2, ecg2, ecg2 );

            // 计算心率,发送心率
            ECG_BPM_Calc( ecg2 );

            emit Signal_BPM_Received( ecg2Bpm, ecg2Bpm, ecg2Bpm );
        }
    }
}

void SerialReceiver::RxData_Handle(char data)
{
    char dataTmp;
    data = data&0x0FF;
    int datamask = data&0x80;
    if(datamask == 0x00)//最高位为0
        this->status = 0;
    //qDebug("status:%d,data:%02X,datamask:%02X",this->status,data&0xFF,datamask);

    switch(this->status)
    {
        case 0:
            if (data == 0x08)//ECG
            {
                this->status = 1;
                this->pkgHead = data;
                this->pkgDataCnt = 0;
//                qDebug()<<"get pkgHead";
            }else
            {
//                qDebug()<<"unknown cmdId"<<data;
            }
            break;
        case 1:
            this->status = 2;
            this->pkgDataHead = data;
//            qDebug()<<"get pkgDataHead";
            break;
        case 2:
            dataTmp = data & 0x7F; //保留数据的第7位
            // 第1个数据的最高位在数据头的最低位中，数据头里保存着数据的最高位所以先根据已经取到几个数据了就向左移动几位让它移动到最后再与01与，就可以
            //得到这个数，最后再向左移动7位回到最高位，这样这个数据就还原了。
            dataTmp = dataTmp | (((this->pkgDataHead >> this->pkgDataCnt) & 0x01) << 7);
            this->pkgData[this->pkgDataCnt] = dataTmp; // 缓存解析后的数据
            this->pkgDataBuf[this->pkgDataCnt] = data; // 缓存解析前的数据
            // 计数器中的值为数据头后面有效数据的字符数
            this->pkgDataCnt = this->pkgDataCnt + 1;

            // 根据通信协议可知数据长度最大为7
            if (this->pkgDataCnt >= 7)
                this->status = 3;

            break;
        case 3:
            // 得到ecg数据
            ecg1 = this->pkgData[0];
            ecg1 = ecg1 << 8;
            ecg1 = ecg1 + this->pkgData[1];
            ecg2 = this->pkgData[2];
            ecg2 = ecg1 << 8;
            ecg2 = ecg1 + this->pkgData[3];
            ecg3 = this->pkgData[4];
            ecg3 = ecg3 << 8;
            ecg3 = ecg3 + this->pkgData[5];

            this->status = 4;
            break;
    }
}

void SerialReceiver::ECG_BPM_Calc(int ecgData)
{
    // 计算脉搏最高值
    ecg2Buff[ecg2BuffIndex] = ecgData;
    ecg2BuffIndex = ecg2BuffIndex + 1;

    if(ecg2BuffIndex >= sizeof(ecg2Buff)/sizeof(int)) // 缓冲区过大会有问题
    {
        ecg2BuffIndex = 0; // 循环缓冲区，用于计算脉搏中值
        ecg2PulseMax = Get_Max(ecg2Buff, sizeof(ecg2Buff)/sizeof(int));
        ecg2PulseMid = (ecg2Zero + ecg2PulseMax)/2; // ecg2Zero 是已知的
    }

    // 找到脉搏
    prePulse = pulse;
    if (ecgData > ecg2PulseMid)
        pulse = 1;
    else
        pulse = 0;

    // 找到脉搏上升沿中值
    if (prePulse == 0 && pulse == 1)
    {
        pulseStart = pulseEnd;
        pulseEnd = QDateTime::currentMSecsSinceEpoch();// current

        // 计算相邻2次脉搏的时间差
        // 求出心率
        ecg2Period = pulseEnd - pulseStart; //
        ecg2Bpm = (int)(60000.00/ecg2Period); // 心率，即每分钟脉搏数量

    }
}

int SerialReceiver::Get_Max(int * data, int len)
{
    // todo
    int first = data[0];
    for(int i = 0;i < len;i++){
        int tem = data[i+1];
        if( first < data[i+1]){
            first = data[i+1];
        }
    }
    return first;
}
