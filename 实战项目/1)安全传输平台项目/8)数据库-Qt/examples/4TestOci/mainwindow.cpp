#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << QSqlDatabase::drivers();

#if 0
    //1. 连接MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");

    //设置主机名
    db.setHostName("192.168.11.47");

    //设置用户名
    db.setUserName("scott");

    //设置密码
    db.setPassword("11");

    //设置数据库
    db.setDatabaseName("orcl");

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
#else
    //1. 连接MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("test.db");

    bool ret = db.open();
    if (ret)
    {
        qDebug() << "连接数据库ok....";
    }
    else
    {
        qDebug() << db.lastError().text();
    }

#endif

}

MainWindow::~MainWindow()
{

}
