#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include<QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
protected:
    //重写父类的鼠标点击事件处理函数
    void mousePressEvent(QMouseEvent *ev);
    //重写父类的鼠标移动事件处理函数
    void mouseMoveEvent(QMouseEvent *ev);
    bool event(QEvent *e);

signals:

public slots:
};

#endif // MYLABEL_H
