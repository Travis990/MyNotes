#include "mybutton.h"
#include<QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

//绘图事件
void MyButton::paintEvent(QPaintEvent *event)
{
    static int num = 1;
    qDebug()<<num++;

    QPushButton::paintEvent(event);
}
