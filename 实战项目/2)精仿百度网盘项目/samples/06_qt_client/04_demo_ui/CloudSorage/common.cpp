#include "common.h"

#include <QFile>
#include <QJsonDocument>    //QJsonDocument要求使用 Qt5, pro文件：QT  += core
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QTime>

void moveToCenter(QWidget *tmp) //窗口在屏幕中央显示
{
     tmp->show(); //显示

     //屏幕中间显示
     QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
     tmp->move((desktop->width() - tmp->width())/2, (desktop->height() - tmp->height())/2);//移动控件
}
