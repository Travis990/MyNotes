#include "mylabel.h"
#include<QDebug>
#include<QMouseEvent>//鼠标事件的头文件
#include"myevent.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    //事件过滤器
    myEvent *ef=new myEvent(this);
    //安装事件过滤器
    this->installEventFilter(ef);

}
//所有的事件类都继承Event
void MyLabel::mousePressEvent(QMouseEvent *ev)
{

    qDebug()<<"按下鼠标";

    //获取鼠标的坐标
    int x=ev->x();
    int y=ev->y();
    //把2个int类型的数据转换成QString
//    QString str=QString("%1,%2").arg(x).arg(y);
//    this->setText(str);

    //获取用户按的是鼠标的左键还是右键或中键
    int button=ev->button();
    QString buttonstr;
    if(button==Qt::LeftButton)
    {
        buttonstr="LeftButton";
    }
    if(button==Qt::RightButton)
    {
         buttonstr="RightButton";
    }
    if(button==Qt::MidButton)
    {
        buttonstr="Mid";

    }

    QString str=QString("<h1><center>pressed[%1,%2][%3]</center></h1>").arg(x).arg(y).arg(buttonstr);
    this->setText(str);

}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //获取鼠标坐标
    int x=ev->x();
    int y=ev->y();

    int button=ev->buttons();
    qDebug()<<button;
    QString btnStr="";
    //button=1
    if(button&Qt::LeftButton)
    {
        btnStr+="LeftButton1";
    }
    //&2个为1才为1
    //0000 0001 & 0000 0001 ==1
    //0000 0001 & 0000 0010 ==0

    //button=2
    if(button&Qt::RightButton)
    {
        btnStr+="RightButton2";
    }
    if(button&Qt::MidButton)
    {
        btnStr+="MidButton4";
    }

    QString str=QString("<h1><center>move[%1,%2][%3]</center></h1>").arg(x).arg(y).arg(btnStr);
    this->setText(str);

}

bool MyLabel::event(QEvent *e)
{
    //返回true，表示这个事件已经被处理
    //如果返回false,表示这个事件没有处理
//    if(e->type()==QEvent::MouseMove)
//    {
//        return true;
//    }
//    if(e->type()==QEvent::MouseButtonPress)
//    {
//        return true;
//    }


    //必须把父类的event事件分发函数返回出去
    return QLabel::event(e);

}
