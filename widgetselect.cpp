#include "widgetselect.h"
#include "ui_widgetselect.h"
#include "patientform.h"
#include "serialreceiver.h"
#include <QPushButton>
#include <QLineEdit>
#include <QStyle>

WidgetSelect::WidgetSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSelect)
{
    //主UI
    ui->setupUi(this);

    //患者1
    patient1 = new Patient( "COM1", "COM2","Gin", "2021/08/21", ":/picture/P1.jpg", 40, 111, this );
    patient1->setGeometry(100, 100, 300, 400);
    patient1->show();
    connect( patient1, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );//患者选择界面到患者1波形界面
    connect( patient1, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );//患者1波形界面返回患者选择界面

    //患者2
    patient2 = new Patient( "COM3", "COM4", "Vodka", "2021/08/24", ":/picture/P2.jpg", 46, 222, this );
    connect( patient2, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );
    connect( patient2, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );
    patient2->setGeometry(450, 100, 300, 400);
    patient2->show();

    //患者3
    patient3 = new Patient( "COM5", "COM6", "Vermouth", "2021/08/11", ":/picture/P3.jpg", 50, 333, this );
    connect( patient3, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );
    connect( patient3, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );
    patient3->setGeometry(800, 100, 300, 400);
    patient3->show();

    //患者4
    patient4 = new Patient( "COM7", "COM8","Sherry", "2021/08/17", ":/picture/P4.jpg", 25, 444, this );
    connect( patient4, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );
    connect( patient4, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );
    patient4->setGeometry(100, 500, 300, 400);
    patient4->show();

    //患者5
    patient5 = new Patient( "COM9", "COM10", "Calvados", "2021/08/28",":/picture/P5.jpg", 27, 555, this );
    connect( patient5, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );
    connect( patient5, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );
    patient5->setGeometry(450, 500, 300, 400);
    patient5->show();

    //患者6
    patient6 = new Patient( "COM11", "COM12","Chianti", "2021/08/21", ":/picture/P6.jpg", 23, 666, this );
    connect( patient6, &Patient::Signal_Select_To_Current, this, &WidgetSelect::Slot_Select_To_Current );
    connect( patient6, &Patient::Signal_Current_To_Select, this, &WidgetSelect::Slot_Current_To_Select );
    patient6->setGeometry(800, 500, 300, 400);
    patient6->show();

    //退出
    QPushButton *quit = new QPushButton(tr("quit"),this);
    quit->setGeometry(1100, 30, 80, 50);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    quit->show();

    //主标题
    QLineEdit *maintitle = new QLineEdit(tr("病人选择界面"),this);
    maintitle->setGeometry(420, 10, 360, 80);
    maintitle->setFont(QFont(tr("Consolas"),  28));
    maintitle->setStyleSheet("{image: url(:/picture/background.jpg);}");
}

WidgetSelect::~WidgetSelect()
{
    delete ui;
}

void WidgetSelect::Slot_Select_To_Current( Patient *patient )//选择界面到实时波形
{
    this->hide();
    patient->widgetCurrent->show();
}

void WidgetSelect::Slot_Current_To_Select( Patient *patient )//实时波形到选择界面
{
    patient->widgetCurrent->hide();
    this->show();
}

