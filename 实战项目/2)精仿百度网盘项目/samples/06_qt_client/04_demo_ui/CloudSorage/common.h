#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] " //没有分号

#include <QWidget>
#include <QString>

//窗口在屏幕中央显示
void moveToCenter(QWidget *tmp);

#endif // COMMON_H

