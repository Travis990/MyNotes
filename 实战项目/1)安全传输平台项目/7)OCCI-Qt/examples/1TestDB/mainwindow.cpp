#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <qDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //1. 创建一个数据库对象
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //2. 设置主机名字
    db.setHostName("192.168.11.53");

    //3. 设置用户名
    db.setUserName("root");

    //4. 设置密码
    db.setPassword("123456");

    //5. 设置端口
    db.setPort(3306);

    //6. 设置使用的数据库
    db.setDatabaseName("test");

    //7. 打开数据库
    bool ret = db.open();
    if (ret)
    {
        qDebug() << "打开数据库ok...";
    }
    else
    {
        qDebug() << db.lastError().text();
    }

    //8. 关闭数据库连接
    db.close();
}

MainWindow::~MainWindow()
{

}
