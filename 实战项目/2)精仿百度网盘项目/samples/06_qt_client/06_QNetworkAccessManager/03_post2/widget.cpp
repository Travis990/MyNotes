#include "widget.h"
#include "ui_widget.h"

#include <QNetworkReply>
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

    //一旦一个QNetworkAccessManager对象被创建了，那么应用程序就可以使用它在网络上发送请求。
    //它提供了一组标准的函数，可以承载网络请求和一些可选的数据，并且每一个请求返回一个QNetworkReply对象。
    //该返回的对象(QNetworkReply对象)包含着返回的请求应带的所有数据。
    manager = new QNetworkAccessManager(this); //新建 QNetworkAccessManager 对象
}

Widget::~Widget()
{
    delete ui;
}

//设置登陆用户信息的json包
QByteArray Widget::setLoginJson(QString user, QString pwd)
{
    QMap<QString, QVariant> login;
    login.insert("user", user);
    login.insert("pwd", pwd);

    /*json数据如下
    {
        user:xxxx,
        pwd:xxx
    }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(login);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}

//按下按钮，发送post请求包
void Widget::on_pushButton_clicked()
{
    //url内容
    QString str = ui->lineEditUrl->text();
    QUrl url(str);

    QNetworkRequest request; //请求对象
    request.setUrl(url); //设置url

    //qt默认的请求头
    //request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //获取用户名和密码
    QString user = ui->lineEditUser->text();
    QString pwd = ui->lineEditPwd->text();
    QByteArray array = setLoginJson(user, pwd ); //组json包

    //设置post数据
    QByteArray data;
    data.append(array);

    //发送post请求
    QNetworkReply *reply = manager->post( request, data );
     if(reply == NULL)
    {
        cout << "reply is NULL";
        return;
    }

    //信号和槽连接, c++ lambda表达式，pro文件增加：   CONFIG += c++11
    connect(reply, &QNetworkReply::finished,
    [=]() mutable
    {
        if (reply->error() != QNetworkReply::NoError) //有错误
        {
            cout << reply->errorString(); //打印错误原因
            reply->deleteLater(); //释放资源
            return;
        }

        QString str = reply->readAll(); //读取服务器回复的内容

        //显示到编辑区
        ui->textEdit->setText(str);

        reply->deleteLater(); //最后要释放 reply 对象
    }
    );

}
