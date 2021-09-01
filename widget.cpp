#include "widget.h"
#include "ui_widget.h"

#include <sqlpatientsmgr.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<PatientData> *list = SqlPatientsMgr::Instance()->SelectPatient("ssh");
    SqlPatientsMgr::Instance()->AddPatientRecord(list->at(0),false);
}

Widget::~Widget()
{
    delete ui;
}

