#include "showdata.h"

#include <QDebug>

ShowData::ShowData(QWidget *parent, QString color1, QString color2 ) : QWidget(parent)
{
    textColor = color1;
    backgroundColor = color2;
    ECGLabel= new QLabel(parent);
    ECGLabel->setStyleSheet( "color:" +textColor  + "; background-color:" + backgroundColor );
    ECGLabel->setFont(QFont("Calibri",35,QFont::Thin));
    ECGLabel->setText("75");

    ECGLabel->setAlignment(Qt::AlignCenter);
    ECGLabel->setGeometry(0,0,129,136);
}

void ShowData::Slot_Data_Handle( int data )
{
    ECGLabel->setText( QString::number( data, 10 ) );

    ECGLabel->show();
}
