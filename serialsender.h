#ifndef SERIALSENDER_H
#define SERIALSENDER_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class SerialSender : public QWidget
{
    Q_OBJECT
public:
    explicit SerialSender(QWidget *parent = nullptr);
    explicit SerialSender(const QString &comName, QWidget *parent = nullptr);
//private:
    QString serialportName = "COM1";
    QSerialPort *com;
    QTimer *timer;
    int ecgDataIndex = 0;
    int Serial_Init(void);
    void Send_EcgPkg();
    char Bcc_Check(char *data, int len);

signals:

};

#endif // SERIALSENDER_H
