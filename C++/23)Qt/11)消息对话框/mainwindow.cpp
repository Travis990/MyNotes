#include "mainwindow.h"
#include<QDebug>
#include<QPushButton>
#include<QMessageBox>//消息，询问，警告等头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,600);

    //1.警告对话框
    QPushButton *btn1 = new QPushButton("警告对话框",this);
    btn1->move(100,100);
    connect(btn1,&QPushButton::clicked,[=]{
        //创建警告对话框
        //第一个参数是父对象，第二个参数是标题，第三个参数是对话框的内容
        QMessageBox::warning(this,"警告","这是警告对话框");
        qDebug()<<"啊啊啊啊";
    });

    //2.询问对话框
    QPushButton *btn2 = new QPushButton("询问对话框",this);
    btn2->move(100,200);
    connect(btn2,&QPushButton::clicked,[=]{
        //创建询问对话框
        //        QMessageBox::question(this,"问你个事","你帅吗?");
        //第四个参数可以设置对话框中的按键
        //        QMessageBox::question(this,"问你个事","你帅吗?",
        //                              QMessageBox::Ok|
        //                              QMessageBox::Cancel);
        //第五个参数是设置对话框中的默认按键
        //        QMessageBox::question(this,"问你个事","你帅吗?",
        //                              QMessageBox::Ok|
        //                              QMessageBox::Cancel,
        //                              QMessageBox::Cancel);

        //通过返回值获取用户按了哪个键
        int ret = QMessageBox::question(this,"问你个事","你帅吗?",
                                        QMessageBox::Ok|
                                        QMessageBox::Cancel,
                                        QMessageBox::Cancel);
        if(ret == QMessageBox::Ok)
        {
            qDebug()<<"按了ok键";
        }
        else
        {
            qDebug()<<"按了Cancel键";
        }
    });

    //3.错误对话框
    QPushButton *btn3 = new QPushButton("错误对话框",this);
    btn3->move(100,300);
    connect(btn3,&QPushButton::clicked,[=]{
        //创建错误对话框
        //第一个参数是父对象，第二个参数是标题，第三个参数是对话框的内容
        QMessageBox::critical(this,"错误","错了");
    });

    //4.陈述对话框
    QPushButton *btn4 = new QPushButton("陈述对话框",this);
    btn4->move(100,400);
    connect(btn4,&QPushButton::clicked,[=]{
        //创建陈述对话框
        //第一个参数是父对象，第二个参数是标题，第三个参数是对话框的内容
        QMessageBox::information(this,"陈述","我是陈述对话框");
    });
}

MainWindow::~MainWindow()
{

}
