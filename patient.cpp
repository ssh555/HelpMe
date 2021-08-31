#include "patient.h"
#include "patientform.h"
#include "widgetcurrent.h"
#include "widgetselect.h"
Patient::Patient( QString comSender, QString comReceiver, QString name, QString date, QString pic_str, int age, int number, QWidget *parent ) : QWidget(parent)
{
    patientForm = new PatientForm( name, date, pic_str, age, number, this );
    patientForm->setObjectName("病人选择界面");
    widgetCurrent = new WidgetCurrent( comSender, comReceiver, name, date, pic_str, age, number );

    connect( patientForm, &PatientForm::Signal_Select_To_Current, this, &Patient::Slot_Select_To_Current );
    connect( widgetCurrent, &WidgetCurrent::Signal_Current_To_Select, this, &Patient::Slot_Current_To_Select );
}

void Patient::Slot_Select_To_Current()
{
    emit Signal_Select_To_Current( this );
}
void Patient::Slot_Current_To_Select()
{
    emit Signal_Current_To_Select( this );
}
