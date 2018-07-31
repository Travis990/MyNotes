#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mybutton *btn1 = new mybutton();

    btn1->setText("自定义按键");
    btn1->setParent(this);

    //对象树
    //1.当父类对象释放时，会先去释放父类对象下所有的子类对象，
    //然后再释放父类对象本身
    //2.所有的对象都继承了QObject
    //3.是父类的析构函数去释放了子类对象
}

Widget::~Widget()
{

}
