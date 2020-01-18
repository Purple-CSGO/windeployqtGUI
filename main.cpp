#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(qAppName() + " - " + APP_VERSION);
    w.show();
    return a.exec();
}
