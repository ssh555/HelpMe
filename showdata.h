#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
#include <QLabel>

class ShowData : public QWidget
{
    Q_OBJECT

public:
    explicit ShowData(QWidget *parent = nullptr, QString color1 = "color:green", QString color2 = "color:gray");
    QLabel *ECGLabel;
    QString textColor;
    QString backgroundColor;

public slots:
    void Slot_Data_Handle( int data );

signals:

};

#endif // SHOWDATA_H
