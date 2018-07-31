#include "widget2.h"
#include<QPushButton>

widget2::widget2(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("窗口2");
    QPushButton *btn2 = new QPushButton("按键2",this);
    this->setFixedSize(800,600);

    connect(btn2,&QPushButton::clicked,[=](){
        //点击按键2，发送自定义信号
        emit this->btn2func();
    });
}
