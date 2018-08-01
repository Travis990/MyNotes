#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>

class Student : public QWidget
{
    Q_OBJECT
public:
    explicit Student(QWidget *parent = nullptr);

signals:
    //信号
    void func();//只要声明，不要实现
    void func2(QString str);
    void func(QString str2);
    void func3();
public slots:
};

#endif // STUDENT_H
