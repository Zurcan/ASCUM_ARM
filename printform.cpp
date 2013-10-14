#include "printform.h"
#include "ui_printform.h"

PrintForm::PrintForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintForm)
{
    ui->setupUi(this);
    //ui->dateTimeEdit->setMaximumDateTime(timeArray[sizeOfArray]);
}

void PrintForm::SetMapMarkerPosition(time_t DateTimePosition)
{
    ui->dateTimeEdit->setDateTime(QDateTime::fromTime_t(DateTimePosition));
}

PrintForm::~PrintForm()
{
    delete ui;
}
