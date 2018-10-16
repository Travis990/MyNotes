#include "widget.h"
#include "ui_widget.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QMap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //1 构建一个json对象
//    QJsonObject obj1;


    //使用QMap来作为json对象
    QMap<QString,QVariant> obj2;

    obj2.insert("name","itcast");
    obj2.insert("age",18);

    //2 构建一个数组
    QJsonArray favorite;
    favorite.append("C++");
    favorite.append("Game");

    obj2.insert("favorite",favorite);

    //转化为json字符串
    //QJsonDocument doc(obj);
    QJsonDocument doc = QJsonDocument::fromVariant(obj2);
    QString json1 = doc.toJson();
    qDebug().noquote()<<json1;


    //从json字符串转化成QJsonObject
    QString json2 = "{\"name\":\"itcast\",\"age\":25}";
    QJsonParseError error;
    QJsonDocument doc2 = QJsonDocument::fromJson(json2.toUtf8(),&error);//解析json可能报错
    if(error.error!=QJsonParseError::NoError)
    {
        qDebug()<<"解析错误："<<error.errorString();
        return;
    }
    QJsonObject obj3 = doc2.object();
    qDebug()<<"name"<<obj3.value("name").toString();
    qDebug()<<"age"<<obj3.value("age").toInt();

}

Widget::~Widget()
{
    delete ui;
}
