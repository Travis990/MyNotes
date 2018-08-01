#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>

class Teacher : public QWidget
{
    Q_OBJECT
public:
    explicit Teacher(QWidget *parent = nullptr);

signals:

public slots:
    //槽函数必须有声明和实现
    void test();
    void test2(QString str);
    void test(QString str);
};

#endif // TEACHER_H
