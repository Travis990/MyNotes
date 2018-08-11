#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);
protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // MYBUTTON_H
