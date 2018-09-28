#include "widget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableView>
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

#if 0

    //查询模型
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM dept");

    for (int i = 0; i < model.rowCount(); ++i) {
        int id = model.record(i).value("id").toInt();
        QString name = model.record(i).value("name").toString();
        QString loc = model.record(i).value("loc").toString();
        qDebug() << id << " " << name << " " << loc;
    }

#endif

#if 0
    //表模型
    QSqlTableModel model;
    model.setTable("dept");
    model.setFilter("id > 10");
    model.setSort(2, Qt::DescendingOrder);
    model.select();

    for (int i = 0; i < model.rowCount(); ++i)
    {
        int id = model.record(i).value("id").toInt();
        QString name = model.record(i).value("name").toString();

        QString loc = model.record(i).value("loc").toString();

        qDebug() << id << " " << name << " " << loc;
    }

#endif

    //MVC   M: model  V: View C:Control
    QSqlTableModel *model = new QSqlTableModel;
    //设置数据库表
    model->setTable("dept");
    //设置排序规则
    model->setSort(0, Qt::AscendingOrder);
    //执行查询
    model->select();

    //设置表头信息
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Loc"));

    QTableView *view = new QTableView(this);
    view->setModel(model);
    view->resize(600, 400);

    //设置为不可以编辑
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);


    view->show();



    //关闭连接
    db.close();
}

Widget::~Widget()
{

}
