#include "patientform.h"
#include "ui_patientform.h"

PatientForm::PatientForm( QString name, QString date, QString pic_str, int age, int number, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::PatientForm)
{
    ui->setupUi(this);

    //设定病人基本信息
    ui->AgeText->setText(QString::number(age, 10));
    ui->NameText->setText(name);
    ui->NemberText->setText(QString::number(number, 10));
    ui->DateText->setText(date);

    //患者照片
    QIcon icon;
    icon.addFile(pic_str);
    ui->PatientPic->setIcon(icon);
    ui->PatientPic->setIconSize(QSize(220, 200));

}

PatientForm::~PatientForm()
{
    delete ui;
}

void PatientForm::on_PatientPic_clicked()
{
    emit Signal_Select_To_Current();
}
