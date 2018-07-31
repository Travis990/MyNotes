#include "widget.h"
#include<QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *btn = new QPushButton("按键1");
    btn->setParent(this);
    /*信号和槽
     * 需求是点击按键，然后窗口关闭
     * 一个按键 （信号发送者)
     * 按键被点击(信号）
     * 一个窗口（信号接收者）
     * 窗口需要关闭（信号处理）
     */
    //建立四者的关系
    connect(btn,&QPushButton::clicked,this,&Widget::close);
}

Widget::~Widget()
{

}
