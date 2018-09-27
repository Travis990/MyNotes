#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建一个对象
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //设置主机名
    db.setHostName("192.168.11.53");
    //设置数据库名
    db.setDatabaseName("test");
    //设置用户名
    db.setUserName("root");
    //设置密码
    db.setPassword("123456");

    //打开连接
    if (db.open())
    {
        qDebug() << "连接数据库Ok....";
    }
    else
    {
        qDebug() << db.lastError().text();
    }

    //查看当前系统支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //获取当前连接
    qDebug() << "ConnectName: " << db.connectionName();
    qDebug() << "ConnectNames:" << QSqlDatabase::connectionNames();

    //获取数据库名字
    qDebug() << "DataBaseName: " << db.databaseName();

    //获取主机名
    qDebug() << "HostName: " << db.hostName();

    //测试数据库是否已经打开
    if (db.isOpen())
    {
        qDebug() << "数据库已经打开....";
    }

    //测试连接是否有效
    if (db.isValid())
    {
        qDebug() << "数据库是有效的...";
    }

    qDebug() << "PassWord: " << db.password();
    qDebug() << "Port: " << db.port();
    qDebug() << "UserName: " << db.userName();
    qDebug() << "tables: " << db.tables();

    //关闭数据库连接
    db.close();
}

MainWindow::~MainWindow()
{

}
