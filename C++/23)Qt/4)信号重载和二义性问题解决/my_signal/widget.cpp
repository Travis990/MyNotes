#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /*
     自定义信号和槽的条件
     自定义信号使用的条件:
     1.必须把信号放到.h中的signals：下面
     2.可以有参数，可以重载
     3.只有声明，没有实现
     4.触发信号:emit object->sig(参数）

     自定义槽使用的条件
     1.只能放到slots下面，qt4模式，qt5版本可以写成静态成员函数
     或全局函数或labmda表达式
     2.void 类型的函数
     3.可以有参数,可以重载
     4.又有声明又有实现
    */

    s = new Student();
    t = new Teacher();

    //connect(s,&Student::func2,t,&Teacher::test2);
    //当信号有二义性问题时，也就是信号重载时
    //connect(s,&Student::func,t,&Teacher::test); error:二义性问题

    //解决方法有两种:
    //第一种方法来解决信号重载时发生的二义性问题
    //函数指针赋值
    void (Student::*Student_string)(QString) = &Student::func;
    void (Teacher::*Teacher_string)(QString) = &Teacher::test;
    //connect(s,Student_string,t,Teacher_string);

    //第二种方式来解决信号重载时发生的二义性问题
    //static_cast
    connect(s,
            static_cast<void (Student::*)(QString)>(&Student::func),
            t,
            static_cast<void (Teacher::*)(QString)>(&Teacher::test)
            );

    //触发信号
    this->myDejan();
}

Widget::~Widget()
{

}

void Widget::myDejan()
{
    //emit s->func2("hello");
    emit s->func();
    emit s->func("带参数");
}
