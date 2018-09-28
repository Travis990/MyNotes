#include "widget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
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

    //3. 创建一个对象
    QSqlQuery query;
#if 0
    //执行插入语句
    ret = query.exec("insert into dept(id, name, loc) "
                     "values(7, '7Name', '7Loc')");

    //执行删除语句
    ret = query.exec("delete from dept where id = 7");



    //执行update语句
    ret = query.exec("update dept set name = '6NAME' where id = 6");


#endif

#if 0
    //第一种形式  名字绑定 名字占位符   :id占一个位置  具体值通过后面进行绑定
    query.prepare("insert into dept(id, name, loc) values(:id, :name, :loc)");
    query.bindValue(":id", 7);
    query.bindValue(":name", "7Name");
    query.bindValue(":loc", "7Loc");

    //第二种形式  位置绑定  名字占位符
    query.prepare("insert into dept(id, name, loc) values(:id, :name, :loc)");
    query.bindValue(0, 8);
    query.bindValue(1, "8name");
    query.bindValue(2, "8Loc");

    //第三种形式  默认位置绑定  名字占位符
    query.prepare("insert into dept(id, name, loc) values(:id, :name, :loc)");

    //绑定按照字段顺序
    query.addBindValue(9);
    query.addBindValue("9name");
    query.addBindValue("9loc");

    //第四种形式  位置占位符
    query.prepare("insert into dept(id, name, loc) values(?, ?, ?)");
    query.bindValue(0, 10);
    query.bindValue(1, "10Name");
    query.bindValue(2, "10Loc");



    //第五种形式 位置占位符
    query.prepare("insert into dept(id, name, loc) values(?, ?, ?)");
    query.addBindValue(11);
    query.addBindValue("11name");
    query.addBindValue("11loc");

    //执行之前准备好的语句
    ret = query.exec();
    if (ret)
    {
        qDebug() << "执行SQL语句ok...";
    }
    else
    {
        qDebug() << query.lastError().text();
    }

#endif

    //批量执行语句
    query.prepare("insert into dept(id, name, loc) values(?, ?, ?)");
    QVariantList ids;
    ids << 21 << 22 << 23 << 24;
    query.addBindValue(ids);

    QVariantList names;
    names << "21name" << "22name" << "23name" << "24name";
    query.addBindValue(names);

    QVariantList locs;
    locs << "21loc" << "22loc" << "23loc" << "24loc";
    query.addBindValue(locs);


    //执行之前准备好的语句
    ret = query.execBatch();
    if (ret)
    {
        qDebug() << "执行SQL语句ok...";
    }
    else
    {
        qDebug() << query.lastError().text();
    }


    //4. 关闭连接
    db.close();
}

Widget::~Widget()
{

}
