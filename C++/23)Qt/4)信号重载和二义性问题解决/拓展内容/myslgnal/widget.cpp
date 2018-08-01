#include "widget.h"
#include<QPushButton>
#include<QDebug>

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


//    s=new Student();
//    t=new Teacher();

   // connect(s,&Student::func2,t,&Teacher::test2);
    //当信号有二义性问题时，也就是信号重载时
    //connect(s,&Student::func,t,&Teacher::test);
    //第一种方法来解决信号重载时发生的二义性问题
    //函数指针赋值
    void (Student::*Student_string)(QString)=&Student::func;
    void (Teacher::*Teacher_string)(QString)=&Teacher::test;
    //connect(s,Student_string,t,Teacher_string);

    //第二种方式来解决信号重载时发生的二义性问题
    //static_cast
//    connect(s,
//            static_cast<void (Student::*)(QString)>(&Student::func),
//            t,
//            static_cast<void (Teacher::*)(QString)>(&Teacher::test)
//            );

    //触发信号
    //this->myMaker();
    qDebug()<<"--------------\n";
    mySignal();
}



Widget::~Widget()
{

}

void Widget::myMaker()
{
//    emit s->func();
//    //emit s->func2("约吗?");
//    emit s->func("带参数");
    emit s->func3();
}

void Widget::mySignal()
{
    s=new Student();
    t=new Teacher();

    //1.一个信号可以连接多个槽函数，槽函数调用是随机的
    //第二个参数是指定这个按键的父类
    QPushButton *btn1=new QPushButton("按键1",this);
//    connect(btn1,&QPushButton::clicked,t,&Teacher::test3);
//    connect(btn1,&QPushButton::clicked,this,&Widget::showMinimized);
//    //2.一个槽函数可以被多个信号连接
    connect(btn1,&QPushButton::clicked,t,&Teacher::test3);
//    connect(s,&Student::func3,t,&Teacher::test3);
//    this->myMaker();
    //3.信号可以连接信号
   // connect(btn1,&QPushButton::clicked,s,&Student::func3);
    //4.信号可以断开
    disconnect(btn1,&QPushButton::clicked,t,&Teacher::test3);
    /*
     1.信号函数和槽函数参数类型必须的对应
     2.信号函数和槽函数的参数个数不一定要相同，但是
     信号函数的参数个数>=槽函数的参数个数
     func2(QString)  test() //OK
     func2(QString)  test(QString) //ok
     func2(QString,int)  test(QString)//ok
      func2(QString,int)  test(int)//no ok
     */

}
