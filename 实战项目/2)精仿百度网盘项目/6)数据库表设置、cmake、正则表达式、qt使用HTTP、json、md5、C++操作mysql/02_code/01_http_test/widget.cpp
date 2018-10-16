#include "widget.h"
#include "ui_widget.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //必须是单例，一个应用程序只有一个QNetworkAccessManager
    this->mManager=new QNetworkAccessManager(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //发送请求到百度，获取页面
    QNetworkRequest req(QUrl("http://www.baidu.com"));
    QNetworkReply *rpl = mManager->get(req);

    //监听reply的信号，等响应到达的时候采取读取数据
    connect(rpl,&QNetworkReply::finished,[=](){
        //判断网络错误
        if(rpl->error()!=QNetworkReply::NoError)
        {
            //输出错误字符串
            qDebug()<<rpl->errorString();
            return ;
        }
        //读取所有数据
        QByteArray arr = rpl->readAll();
        QString content = arr;
        //输出到控件
        this->ui->textEdit->setText(content);
        this->ui->plainTextEdit->setPlainText(content);

        //rpl要手动释放，但是不能直接使用delete
        rpl->deleteLater();//延时释放

    });

}

void Widget::on_pushButton_2_clicked()
{
    //发送post请求到echo 的fastCGI
    //发送请求到百度，获取页面
    QNetworkRequest req(QUrl("http://192.168.177.170/test"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QString json = "{\"name\":\"itcast\",\"age\":18}";


    QNetworkReply *rpl = mManager->post(req,json.toUtf8());

    //监听reply的信号，等响应到达的时候采取读取数据
    connect(rpl,&QNetworkReply::finished,[=](){
        //判断网络错误
        if(rpl->error()!=QNetworkReply::NoError)
        {
            //输出错误字符串
            qDebug()<<rpl->errorString();
            return ;
        }
        //读取所有数据
        QByteArray arr = rpl->readAll();
        QString content = arr;
        //输出到控件
        this->ui->textEdit->setText(content);
        this->ui->plainTextEdit->setPlainText(content);

        //rpl要手动释放，但是不能直接使用delete
        rpl->deleteLater();//延时释放

    });




}
