#include "widget.h"
#include<QDebug>
#include<QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //lambda
    //用函数指针来获取地址
    void (*p)()=[]()//这只是函数的定义
    {
        qDebug()<<"hello";
    };

    p();//调用函数

    //2.[]的作用
    int a=10;
    [](int a1)//这是形参
    {
        qDebug()<<"a="<<a1;
    }(a);//调用函数

    [a]()//从外面捕获a
    {
        qDebug()<<"a="<<a;
    }();

    int b=20;
    int c=30;
    //=时，或直接捕获widget构造函数中的局部变量时，这时这些局部
    //变量是以const的形式传递到函数中的
    //如果要改变局部变量的值，加上mutable
    [=]()mutable//如果中括号中的=，把widget构造函数中所有的局部变量传递到函数中
    {
       qDebug()<<"=";
       qDebug()<<"a="<<a;
       qDebug()<<"b="<<b;
       qDebug()<<"c="<<c;
       a=100;
    }();
    qDebug()<<"a="<<a;
    [&]()//如果中括号中的&，把widget构造函数中所有的局部变量引用到函数中
    {
       qDebug()<<"&";
       qDebug()<<"a="<<a;
       qDebug()<<"b="<<b;
       qDebug()<<"c="<<c;
       a=100;
    }();
    qDebug()<<"a="<<a;

    //[&,b]()//表示b是值传递，其他是引用
    //[=,&b]()表示b是引用，其他是值传递
    [&,b]()//表示b是值传递，其他是引用
    {

    }();
    qDebug()<<"-----------------\n";
    QPushButton *btn=new QPushButton("按键",this);
    connect(btn,&QPushButton::clicked,
            [=](){//不要用引用，因为abc都是局部变量
        qDebug()<<"a="<<a;
        qDebug()<<"b="<<b;
        qDebug()<<"c="<<c;
        //this;//不是局部变量，可以使用
    });
    //可以有返回值
    int num=[]()->int{return 10;}();
    qDebug()<<"num="<<num;
    qDebug()<<"构造函数结束\n";

}

Widget::~Widget()
{

}
