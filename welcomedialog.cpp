#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);

    tmpIcon = new QIcon(":new/p/flashSilverP");
    ui->pushButton->setIcon(*tmpIcon);
    tmpIcon = new QIcon(":new/p/hardDriveI");
    ui->pushButton_2->setIcon(*tmpIcon);

}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}
