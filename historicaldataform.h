#ifndef HISTORICALDATAFORM_H
#define HISTORICALDATAFORM_H

#include <QWidget>

namespace Ui {
class HistoricalDataForm;
}

class HistoricalDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit HistoricalDataForm(QWidget *parent = nullptr);
    ~HistoricalDataForm();

private:
    Ui::HistoricalDataForm *ui;
};

#endif // HISTORICALDATAFORM_H
