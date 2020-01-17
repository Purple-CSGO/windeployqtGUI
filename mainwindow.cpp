#include "mainwindow.h"
#include "ui_mainwindow.h"

QString toolPath = "";
QString deployPath = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //未引入拖拽之前为了快速debug设计
    toolPath = ui->toolPath->text();
    deployPath = ui->deployPath->text();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolPathSelect_clicked()
{   //选择windeployqt.exe位置
    QString tPath = QFileDialog::getOpenFileName(this, "选择windeployqt.exe", ".", "windeployqt.exe");
    if( !QString(tPath).isEmpty() )
        toolPath = tPath;
    ui->toolPath->setText(toolPath);
}

void MainWindow::on_deployPathSelect_clicked()
{   //选择Qt程序位置
    QString tPath = QFileDialog::getOpenFileName(this, "选择Qt源程序", ".", "*.exe");
    if( !QString(tPath).isEmpty() )
        deployPath = tPath;
    ui->deployPath->setText(deployPath);
}

void MainWindow::on_Start_clicked()
{   //调用CMD，deploy Qt程序
    if( QString(toolPath).isEmpty() || QString(deployPath).isEmpty() )
        return;
    toolPath = ui->toolPath->text();
    deployPath = ui->deployPath->text();

    QProcess p;
    QString command = toolPath + " " + deployPath + " " + "-no-angle -no-opengl-sw";

    p.start(command);    //p.start第一个command似乎不能接受空格
    p.waitForStarted();
    p.closeWriteChannel();  //关闭写通道 ，解决未响应问题
    p.waitForFinished();
    QString OutMsg = QString::fromLocal8Bit(p.readAllStandardOutput());
    QString ErrMsg = QString::fromLocal8Bit(p.readAllStandardError());
    if( !QString(ErrMsg).isEmpty() )
        QMessageBox::warning(this, "发生错误", ErrMsg);
    ui->textEdit->setText(OutMsg);
    //QMessageBox::warning(this, "提示",cmdOutput);
}
