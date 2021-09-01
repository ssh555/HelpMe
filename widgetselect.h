#ifndef WIDGETSELECT_H
#define WIDGETSELECT_H

#include "patient.h"
#include "patientform.h"
#include "widgetcurrent.h"
#include <QWidget>

namespace Ui {
class WidgetSelect;
}

class WidgetSelect : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSelect(QWidget *parent = nullptr);
    ~WidgetSelect();
    Patient *patient1;
    Patient *patient2;
    Patient *patient3;
    Patient *patient4;
    Patient *patient5;
    Patient *patient6;

private:
    Ui::WidgetSelect *ui;

private slots:
    void Slot_Select_To_Current( Patient *patient );
    void Slot_Current_To_Select( Patient *patient );

};

#endif // WIDGETSELECT_H
