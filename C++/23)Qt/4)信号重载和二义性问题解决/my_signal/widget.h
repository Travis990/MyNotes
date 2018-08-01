#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"student.h"
#include"teacher.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    //触发信号
    void myDejan();
private:
    Student *s;
    Teacher *t;
};

#endif // WIDGET_H
