#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QString appName = "windeployqtGUI", version = "V0.2";   //应用名和版本号
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(appName + " - " + version);
    w.show();
    return a.exec();
}
