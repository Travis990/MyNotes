#ifndef MYEVENT_H
#define MYEVENT_H

#include <QObject>

class myEvent : public QObject
{
    Q_OBJECT
public:
    explicit myEvent(QObject *parent = nullptr);
    /*
     * 事件过滤器
     * 事件传输到窗口之前会到事件过滤器
     * 1.窗口使用事件过滤器需要安装
     * 2.事件过滤器是object的对象或者说是object是子类对象
     * 3.对象可以作为自己的事件过滤器
     *
     */
    bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:
};

#endif // MYEVENT_H
