#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QJsonDocument>    //QJsonDocument要求使用 Qt5, pro文件：QT  += core
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] " //没有分号

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    test1(); //读json数组

    //test2(); //生成普通键值对json

    //test3();  //写json数组

    //test4();

    //test5();

    //test6(); //读配置文件
}

Widget::~Widget()
{
    delete ui;
}

//读json数组
void Widget::test1()
{
    QFile file("../MyJsonDocument/test.json");

    if( false == file.open(QIODevice::ReadOnly) ) //打开失败
    {
        cout << "file open err";
        return;
    }

    QByteArray json = file.readAll(); //读取所有内容
    cout << json.data();

    //关闭文件
    file.close();

    /*
        {
            "files":
            [
                {
                    "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4",
                    "filename": "test.mp4",
                     "user": "yoyo"
                },
                {
                    "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z07823.mp4",
                    "filename": "test2.mp4",
                     "user": "itcast"
                }
            ]
        }
    */

    QJsonParseError error;

    //将来源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if( doc.isObject())
        {
            //QJsonObject json对象，描述json数据中{}括起来部分
            QJsonObject obj = doc.object();//取得最外层这个大对象
            QStringList keyList = obj.keys(); //获取key值
            cout << "obj.keys()" << keyList; //("files")

            //获取games所对应的数组
            //QJsonArray json数组，描述json数据中[]括起来部分
            QJsonArray array = obj.value("files").toArray();

            int size = array.size();   //数组个数
            cout << "size = " << size;

            for(int i = 0; i < size; ++i)
            {

                QJsonObject tmp = array[i].toObject(); //取第i个对象
                //cout << "tmp.size()  = " << tmp.size();
                cout << "\ni = " << i;

                QStringList keyList = tmp.keys();   //获取所有的key值
                for(int i = 0; i < keyList.size(); ++i)
                {
                    //QJsonValue 用于描述键值对的值部分
                    //tmp.value(keyList.at(i)).toString()
                    //取出keyList.at(i)所对应的value
                    cout << keyList.at(i) << ":" << tmp.value(keyList.at(i)).toString().toStdString().data();
                }

            }
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }
}

void Widget::test2()
{
    QVariantList list;

    QVariantMap redis;
    redis.insert("ip", "127.0.0.1");
    redis.insert("port", "6379");


    QVariantMap mysql;
    mysql.insert("ip", "127.0.0.1");
    mysql.insert("port", "3306");
    mysql.insert("database", "dfs");
    mysql.insert("user", "root");
    mysql.insert("password", "123456");

    list << redis << mysql;

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(list);
    if (!jsonDocument.isNull())
    {
        cout << jsonDocument.toJson().data();
    }

    /*
    [
        {
            "ip": "127.0.0.1",
            "port": "6379"
        },

        {
            "database": "dfs",
            "ip": "127.0.0.1",
            "password": "123456",
            "port": "3306",
            "user": "root"
        }
    ]

    */
}

void Widget::test3()
{
    /*
        {
        "files":
            [
                {
                "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4",
                "filename": "test.mp4",
                "user": "itcast"
                },

                {
                "url": "http://192.168.31.109:80/group1/M00/00/00/wKgCbFepTp2AUnd1AFRAAvu2TSg259.mp3",
                "filename": "陈奕迅 - 红玫瑰.mp3",
                "user": "itcast"
                }
            ]
        }
    */

    //从外层向内层设，遇到 "{" 用QMap<QString, QVariant>，遇到 "[" 用QList<QVariant>

    QMap<QString, QVariant> json;

    QVariantList list;

    QVariantMap tmp1;
    tmp1.insert("url", "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4");
    tmp1.insert("filename", "test.mp4");
    tmp1.insert("user", "itcast");

    QVariantMap tmp2;
    tmp2.insert("url", "http://192.168.31.109:80/group1/M00/00/00/wKgCbFepTp2AUnd1AFRAAvu2TSg259.mp3");
    tmp2.insert("filename", "陈奕迅 - 红玫瑰.mp3");
    tmp2.insert("user", "itcast");

    list << tmp1 << tmp2;

    json.insert("files", list);

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(json);
    if (!jsonDocument.isNull())
    {
        cout << jsonDocument.toJson().data();
    }

    QFile file("../MyJsonDocument/test3.json");

    if( false == file.open(QIODevice::WriteOnly) ) //打开失败
    {
        cout << "file open err";
        return;
    }

    file.write( jsonDocument.toJson() ); //json内容写入文件

    file.close();

}

void Widget::test4()
{
    //QVariant类作为一个最为普遍的Qt数据类型的联合
    //QVariant为一个万能的数据类型--可以作为许多类型互相之间进行自动转换。
    QMap<QString, QVariant> json;

    QMap<QString, QVariant> redis;
    QMap<QString, QVariant> mysql;

    redis.insert("ip", "127.0.0.1");
    redis.insert("port", "6379");


    mysql.insert("ip", "127.0.0.1");
    mysql.insert("port", "3306");
    mysql.insert("database", "dfs");
    mysql.insert("user", "root");
    mysql.insert("password", "123456");

    json.insert("redis", redis);
    json.insert("mysql", mysql);

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(json);
    if (!jsonDocument.isNull())
    {
        cout << jsonDocument.toJson().data();
    }

    //输出结果：
    /*
        {
            "mysql": {
                "database": "dfs",
                "ip": "127.0.0.1",
                "password": "123456",
                "port": "3306",
                "user": "root"
            },
            "redis": {
                "ip": "127.0.0.1",
                "port": "6379"
            }
        }

    */
}

void Widget::test5()
{
    //从外层向内层设，遇到 "{" 用QMap<QString, QVariant>，遇到 "[" 用QList<QVariant>。
    QMap<QString, QVariant> map1;
    QList<QVariant> list2;
    QMap<QString, QVariant> map3;
    QMap<QString, QVariant> map4_1;
    QMap<QString, QVariant> map4_2;

    map4_1.insert("姓名", "itcast");
    map4_1.insert("性别", "男");
    map4_1.insert("年龄", "18");

    map4_2.insert("姓名", "lily");
    map4_2.insert("性别", "女");
    map4_2.insert("年龄", "22");

    map3.insert("0",map4_1);
    map3.insert("1",map4_2);

    list2.append(map3);

    map1.insert("资料", list2);

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(map1);
    if (!jsonDocument.isNull())
    {
        cout << jsonDocument.toJson().data();
    }

    /*
        {
            "资料": [
                {
                    "0": {
                        "姓名": "itcast",
                        "年龄": "18",
                        "性别": "男"
                    },
                    "1": {
                        "姓名": "lily",
                        "年龄": "22",
                        "性别": "女"
                    }
                }
            ]
        }

    */
}

void Widget::test6()
{
     QFile file("../MyJsonDocument/cfg.json");

    if( false == file.open(QIODevice::ReadOnly) ) //打开失败
    {
        cout << "file open err";
        return;
    }

    QByteArray json = file.readAll(); //读取所有内容
    //cout << json.data();

    //关闭文件
    file.close();

    /*
      {
        "redis":
        {
            "ip": "127.0.0.1",
            "port": "6379"
        },

        "mysql":
        {
            "ip": "127.0.0.1",
            "port": "3306",
            "database": "dfs",
            "user": "root",
            "password": "123456"
        }
    }
    */

    QJsonParseError error;

    //将来源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if( doc.isObject())
        {
            //QJsonObject json对象，描述json数据中{}括起来部分
            QJsonObject obj = doc.object();//取得最外层这个大对象
            QStringList keyList = obj.keys(); //获取key值
            cout << "obj.keys()" << keyList;

           for(int i = 0; i < keyList.size(); ++i)
           {
                 QJsonObject tmp = obj.value( keyList.at(i) ).toObject();
                 cout << keyList.at(i);

                 QStringList list = tmp.keys();
                 for(int i = 0; i < list.size(); ++i)
                 {
                    cout << list.at(i) << ":" << tmp.value( list.at(i) ).toString();
                 }
           }


        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }
}
