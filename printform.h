#ifndef PRINTFORM_H
#define PRINTFORM_H

#include <QDialog>

//#include <mainwindow.h>
namespace Ui {
class PrintForm;
}

class PrintForm : public QDialog
{
    Q_OBJECT

public:
    explicit PrintForm(QWidget *parent = 0);
    void SetMapMarkerPosition(time_t DateTimePosition);
    QDateTime returnFromTime();
    QDateTime retutnToTime();
    ~PrintForm();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::PrintForm *ui;
};

#endif // PRINTFORM_H
