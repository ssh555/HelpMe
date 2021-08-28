#include "historicaldataform.h"
#include "ui_historicaldataform.h"

HistoricalDataForm::HistoricalDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoricalDataForm)
{
    ui->setupUi(this);
}

HistoricalDataForm::~HistoricalDataForm()
{
    delete ui;
}
