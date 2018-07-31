#include "widget.h"
#include <QApplication>
#include <QPushButton>//按键的头文件

int main(int argc, char *argv[])
{
    //应用程序，类实例化的对象，每个工程有且只有一个
    QApplication a(argc, argv);
    //实例化一个窗口对象
    Widget w;

    //QT内置类，实例化一个对象
    QPushButton btn;
    //设置按键上显示的名字
    btn.setText("按钮1");
    //btn.show();
    //建立父子关系
    //第一种方法
    btn.setParent(&w);

    //第二种方法
    QPushButton btn2(&w);
    btn2.setText("按键2");
    //设置按键在窗口的位置
    btn2.move(200,100);
    //设置按键的大小
    btn2.resize(100,100);


    //把窗口对象显示出来
    w.show();
    //QT窗口的原点在左上角，往右是x增加，往下是y增加

    w.setWindowTitle("窗口标题");
    //程序生命循环，消息循环
    return a.exec();
}
