#include "mainwindow.h"
#include<QPushButton>
#include<QFileDialog>//文件对话框的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,600);

    //文件对话框
    QPushButton *btn = new QPushButton("文件对话框",this);
    btn->move(300,300);
    connect(btn,&QPushButton::clicked,[=]{
        //QFileDialog::getOpenFileName(this,"标题");
        //第三个参数是改变默认的路径
        //QFileDialog::getOpenFileName(this,"标题","E:/");

        //第四个参数是设置过滤文件格式
        QFileDialog::getOpenFileName(this,"标题",
                                     "D:\\github\\mynotes\\C++\\23)Qt\\8)可视化添加组件操作&导入资源\\Image",
                                     "ALL(*.*);;PNG(*.png);;JPG(*.jpg);;GIF(*.gif)"
                                     );
    });
}

MainWindow::~MainWindow()
{

}
