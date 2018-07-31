#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *la = new QLabel("左侧部件",this);
    ui->statusBar->addWidget(la);
    //用绝对路径的方式引入资源,路径需要注意，需要QT的路径模式
    ui->actionnew->setIcon(QIcon("D:/github/mynotes/C++/23)Qt/8)可视化添加组件操作&导入资源/Image/Luffy.png"));
    //把资源引入到工程中
    /*
     1.把资源放到和.pro文件同一层目录中
     2.创建文件,是qt的资源文件夹
     3.添加资源
    */
    ui->actionnew2->setIcon(QIcon(":/Image/OnePiece.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
