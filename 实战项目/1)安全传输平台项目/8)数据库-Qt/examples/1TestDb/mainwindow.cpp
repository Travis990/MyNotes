#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //1. 连接MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //设置主机名
    db.setHostName("192.168.11.47");

    //设置用户名
    db.setUserName("root");

    //设置密码
    db.setPassword("123456");

    //设置数据库
    db.setDatabaseName("test");

    //2. 连接数据库
    bool ret = db.open();
    if (ret)
    {
        qDebug() << "连接数据库ok ...";
    }
    else
    {
        qDebug() << db.lastError().text();
        return;
    }

    //3. 执行查询语句
    //QSqlQuery query("select * from dept");
    QSqlQuery query;

    query.exec("select * from dept where id > 2");

    //4. 循环获取查询的结果
    while(query.next())
    {
    #if 0
        //第一种情形: 清楚对应字段编号
        qDebug() << query.value(0).toInt() << " " << query.value(1).toString() << " " << query.value(2).toString();
    #else
        //第二种情形: 不清楚对应字段的编号  通过字段名字获取对应的编号
        qDebug() << query.value(query.record().indexOf("id")).toInt()
                 << query.value(query.record().indexOf("name")).toString()
                 << query.value(query.record().indexOf("loc")).toString();
    #endif
    }

    //5. 关闭连接
    db.close();

}

MainWindow::~MainWindow()
{

}
