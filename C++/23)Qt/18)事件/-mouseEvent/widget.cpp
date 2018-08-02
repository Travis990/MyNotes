#include "widget.h"
#include "ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //当用户在程序中点击鼠标，点击鼠标事件会被系统自动发送给QWidget这个类中
    //这个类中有很多事件处理函数，我们用户只需要继承这虚函数，重写父类的虚函数

}

Widget::~Widget()
{
    delete ui;
}


