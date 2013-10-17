#include "printform.h"
#include "ui_printform.h"

PrintForm::PrintForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintForm)
{
    ui->setupUi(this);
    //ui->dateTimeEdit->setMaximumDateTime(timeArray[sizeOfArray]);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(accept()));
            connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(reject()));
}

void PrintForm::SetMapMarkerPosition(time_t DateTimePosition)
{
    QVariant tmp1, tmp2;
    ui->dateTimeEdit->setDateTime(QDateTime::fromTime_t(DateTimePosition));
    tmp1 = ui->dateTimeEdit->dateTime();
    tmp2 = ui->dateTimeEdit_2->dateTime();
    if((int)(tmp1.toInt()-tmp2.toInt())<120)
    ui->dateTimeEdit_2->setDateTime(QDateTime::fromTime_t(DateTimePosition+120));

}
QDateTime PrintForm::returnFromTime()
{
    return ui->dateTimeEdit->dateTime();
}

QDateTime PrintForm::retutnToTime()
{
    return ui->dateTimeEdit_2->dateTime();
}

PrintForm::~PrintForm()
{
    delete ui;
}

void PrintForm::on_pushButton_clicked()
{

}
