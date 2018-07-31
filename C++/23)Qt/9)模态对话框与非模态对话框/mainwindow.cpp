#include "mainwindow.h"
#include<QDialog>//对话框的头文件
#include<QDebug>
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,600);
    QPushButton *btn = new QPushButton("模态对话框",this);
    connect(btn,&QPushButton::clicked,[=](){
        //创建一个模态对话框
        //在程序中只能操作对话框
        QDialog dlg(this);
        dlg.exec();//阻塞
        qDebug()<<"aaaaaa";
    });

    QPushButton *btn2 = new QPushButton("非模态对话框",this);
    btn2->move(200,200);
    connect(btn2,&QPushButton::clicked,[=](){
        //创建非模态对话框
        //        QDialog dlg(this);
        //        dlg.show();

        QDialog *dlg = new QDialog(this);
        dlg->show();
        //关闭窗口时释放对象
        dlg->setAttribute(Qt::WA_DeleteOnClose);
    });
}

MainWindow::~MainWindow()
{

}
