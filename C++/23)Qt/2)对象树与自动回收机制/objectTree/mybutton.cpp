#include "mybutton.h"
#include <QDebug>//打印字符串的头文件

mybutton::mybutton(QPushButton *parent) : QPushButton(parent)
{

}

mybutton::~mybutton()
{
    qDebug()<<"mybutton delete";
}
