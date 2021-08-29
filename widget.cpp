#include "widget.h"
#include "ui_widget.h"

#include <sqlpatientsmgr.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<PatientData> *list = SqlPatientsMgr::Instance()->SelectPatient("ssh");
    ui->labelID->setText(QString::number(list->at(0).id));
    ui->labelage->setText(QString::number(list->at(0).age));
    ui->labelName->setText(QString(list->at(0).name));
    ui->labelHTPDate->setText(list->at(0).HPTDate.toString());
    ui->labelphoto->setPixmap(list->at(0).photo);
    ui->labelIDCardNum->setText(list->at(0).IDCardNum);
    SqlPatientsMgr::Instance()->AddPatientRecord(list->at(0),false);
    /*测试代码
    */
}

Widget::~Widget()
{
    delete ui;
}

