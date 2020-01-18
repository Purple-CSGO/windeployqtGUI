#include "mainwindow.h"
#include "ui_mainwindow.h"

QString toolPath = "";
QString deployPath = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    toolPath = ui->toolPath->text();
    deployPath = ui->deployPath->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//选择windeployqt.exe位置
void MainWindow::on_toolPathSelect_clicked()
{
    QString tPath = QFileDialog::getOpenFileName(this, "选择windeployqt.exe", ".", "windeployqt.exe");
    if( !QString(tPath).isEmpty() )
        toolPath = tPath;
    ui->toolPath->setText(toolPath);
}

//选择Qt程序位置
void MainWindow::on_deployPathSelect_clicked()
{
    QString tPath = QFileDialog::getOpenFileName(this, "选择Qt源程序", ".", "*.exe");
    if( !QString(tPath).isEmpty() )
        deployPath = tPath;
    ui->deployPath->setText(deployPath);
}

//调用CMD，deploy Qt程序
void MainWindow::on_Start_clicked()
{
    toolPath = ui->toolPath->text();
    deployPath = ui->deployPath->text();
    if( QString(toolPath).isEmpty() || QString(deployPath).isEmpty() )
        return;

    QProcess p;
    QString command = toolPath + " " + deployPath + " " + "-no-angle -no-opengl-sw";
    p.start(command);
    p.waitForStarted();
    p.closeWriteChannel();  //关闭写通道 ，解决未响应问题
    p.waitForFinished();
    QString OutMsg = QString::fromLocal8Bit(p.readAllStandardOutput());
    QString ErrMsg = QString::fromLocal8Bit(p.readAllStandardError());
    if( !QString(ErrMsg).isEmpty() )
        QMessageBox::warning(this, "发生错误", ErrMsg);
    else
        QMessageBox::warning(this, "成功", "");
}

//支持拖拽文件和粘贴拖拽路径文本 [注意设置文本为空&cursorwidth=0&添加placeholder]
//TODO: placeholder只能单行显示 复杂项目`拖拽区域`的显示可能有问题
void MainWindow::on_dragArea_textChanged()
{
    QString tPath = ui->dragArea->toPlainText();
    //处理toolPath
    if( tPath.endsWith("windeployqt.exe",Qt::CaseSensitive) ){
        tPath.replace("file:///","");        //去除拖拽产生的前缀
        /*  //找到串中最后一个"file:///"的位置并删除"..."及以前的位置
                int i = tPath.lastIndexOf("file:///");
                if(  i != -1 )
                    tPath.remove(0, i + QString("file:///").length() );
        */

        //该路径文件存在时设置路径
        if(QFile::exists(tPath))
            ui->toolPath->setText(tPath);
    }
    //处理deployPath
    else if( tPath.endsWith(".exe",Qt::CaseSensitive) ){
        tPath.replace("file:///","");        //去除拖拽产生的前缀

        //该路径文件存在时设置路径
        if(QFile::exists(tPath))
            ui->deployPath->setText(tPath);
    }

    //拖拽区域文本置空
    if( !QString(tPath).isEmpty() )
        ui->dragArea->setText("");
}

