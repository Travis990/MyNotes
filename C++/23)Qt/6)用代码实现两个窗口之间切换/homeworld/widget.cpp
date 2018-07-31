#include "widget.h"
#include<QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口的名字
    this->setWindowTitle("窗口1");
    //创建按键1
    QPushButton* btn1 = new QPushButton("按钮1",this);
    //设置窗口的大小
    this->setFixedSize(400,300);

    //点击按键发送信号
    connect(btn1,&QPushButton::clicked,[=](){
        //按下按键1，执行这里的代码
        //显示窗口2
        w2.show();
        //隐藏自己
        this->hide();
    });

    //接收信号
    connect(&w2,&widget2::btn2func,[=](){
        //点击按键2，执行这里的代码
        //隐藏自己
        w2.hide();
        //显示窗口1
        this->show();
    });
}

Widget::~Widget()
{

}
