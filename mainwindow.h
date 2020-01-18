#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
//#include <QtDebug>
//#include <QDragEnterEvent>
//#include <QDropEvent>
//#include <QMimeData>
//#include <QTextEdit>

#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolPathSelect_clicked();

    void on_deployPathSelect_clicked();

    void on_Start_clicked();

    void on_dragArea_textChanged();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
