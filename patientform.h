#ifndef PATIENTFORM_H
#define PATIENTFORM_H

#include "widgetcurrent.h"
#include <QWidget>

namespace Ui {
class PatientForm;
}

class PatientForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientForm( QString name = "ssh", QString date = "feb", QString pic_str = ":/picture/P1.jpg", int age = 32, int number = 34, QWidget *parent = nullptr);
    ~PatientForm();

private slots:

    void on_PatientPic_clicked();

private:
    Ui::PatientForm *ui;
signals:
    void Signal_Select_To_Current();
    //void Signal_Current1_To_Select( WidgetCurrent *widgetCurrent );
};

#endif // PATIENTFORM_H
