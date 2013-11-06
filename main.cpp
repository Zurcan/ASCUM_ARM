#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setContentsMargins(0,0,0,-30);
    w.show();
    
    return a.exec();
}
