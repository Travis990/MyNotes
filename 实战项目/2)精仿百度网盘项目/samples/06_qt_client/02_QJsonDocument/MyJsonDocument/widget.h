#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void test1();   //读json数组
    void test2();   //生成普通键值对json
    void test3();   //生成json数组
    void test4();
    void test5();
    void test6();   //解析普通json文件

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
