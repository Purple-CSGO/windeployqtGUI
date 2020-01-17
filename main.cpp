#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QString version = "V0.1";   //版本号
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("windeployqtGUI - " + version);
    w.show();
    return a.exec();
}
