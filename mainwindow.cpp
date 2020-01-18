#include "mainwindow.h"
#include "ui_mainwindow.h"

QString toolPath = "";
QString deployPath = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->deployPath->setAcceptDrops(true);
    ui->deployPath->setDragEnabled(true);
    //未引入拖拽之前为了快速debug设计
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

    p.start(command);    //p.start第一个command似乎不能接受空格
    p.waitForStarted();
    p.closeWriteChannel();  //关闭写通道 ，解决未响应问题
    p.waitForFinished();
    QString OutMsg = QString::fromLocal8Bit(p.readAllStandardOutput());
    QString ErrMsg = QString::fromLocal8Bit(p.readAllStandardError());
    if( !QString(ErrMsg).isEmpty() )
        QMessageBox::warning(this, "发生错误", ErrMsg);
    //ui->dragArea->setText(OutMsg);
    else
        QMessageBox::warning(this, "成功", "");
}

//读取文本内容
bool MainWindow::readFile(const QString &fileName)
{
    bool r = false;
    QFile file(fileName);
    QString content;
    if(file.open(QIODevice::ReadOnly)) {    //一定注意设置为只读
        content = file.readAll();
        r = true;
    }
    textEdit->setText(content);
    return r;
}

//利用QString的remove find file:///        支持拖拽文件和粘贴拖拽路径文本
//注意设置文本为空
void MainWindow::on_dragArea_textChanged()
{
    QString tPath = ui->dragArea->toPlainText();
    if( tPath.endsWith("windeployqt.exe",Qt::CaseSensitive) ){
        //去除拖拽产生的前缀
        int i = tPath.lastIndexOf("file:///");
        if(  i != -1 )
            tPath.remove(0, i + QString("file:///").length() );

        //该路径文件存在时设置路径
        if(QFile::exists(tPath))
            ui->toolPath->setText(tPath);
    }
    else if( tPath.endsWith(".exe",Qt::CaseSensitive) ){
        //去除拖拽产生的前缀
        int i = tPath.lastIndexOf("file:///");
        if(  i != -1 )
            tPath.remove(0, i + QString("file:///").length() );

        //该路径文件存在时设置路径
        if(QFile::exists(tPath))
            ui->deployPath->setText(tPath);
    }
    //拖拽区域文本置空
    if( !QString(tPath).isEmpty() )
        ui->dragArea->setText("");
}

