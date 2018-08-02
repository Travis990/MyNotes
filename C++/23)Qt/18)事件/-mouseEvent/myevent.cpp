#include "myevent.h"
#include<QEvent>

myEvent::myEvent(QObject *parent) : QObject(parent)
{

}

bool myEvent::eventFilter(QObject *watched, QEvent *event)
{
//返回true,表示该事件受到拦截，不会传递到窗口
    if(event->type()==QEvent::MouseMove)
    {
        return true;
    }

    return false;

}
