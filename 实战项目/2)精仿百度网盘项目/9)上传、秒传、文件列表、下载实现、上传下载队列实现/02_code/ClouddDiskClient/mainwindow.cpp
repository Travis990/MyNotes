#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->pushButton_upload_one_file,&QPushButton::clicked,[=](){
        //上传一个文件，显示在上传的任务队列里边
        this->ui->widget_transfer_tab_widget->appendUploadTask("/Users/itcast/Desktop/07_上传下载队列的实现思路.mp4","07_上传下载队列的实现思路.mp4");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
