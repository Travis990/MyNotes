#include "widget.h"
#include "ui_widget.h"
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

    //关联信号和槽
    //manager只要发送请求成功，它就会下载数据(接收服务器回复的数据)。而当数据下载完成后，manager会发出 finished()信号
    connect(manager, &QNetworkAccessManager::finished,
                this, &Widget::slotFinished);

    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)) );


}

Widget::~Widget()
{
    delete ui;
}

//按下按钮，发送get请求
void Widget::on_pushButton_clicked()
{
    //获取用户名和密码, 服务器ip, port
    QString user = ui->lineEditUser->text();
    QString pwd = ui->lineEditPwd->text();
    QString ip = ui->lineEditIP->text();
    QString port = ui->lineEditPort->text();

    //url 包
    QString url = QString("http://%1:%2/login?type=10&user=%3&pwd=%4")
                    .arg(ip).arg(port).arg(user).arg(pwd);
    cout << "url = " << url.toStdString().data();

    //发送get请求
    manager->get( QNetworkRequest(QUrl(url)) );

}

//槽函数，
void Widget::slotFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) //没有错误
    {
         QString str = reply->readAll(); //读取服务器回复的内容

        //显示到编辑区
        ui->textEdit->setText(str);
    }
    else //出错
    {
        //reply->error()
        cout << reply->errorString();
    }

    reply->deleteLater(); //最后要释放 reply 对象

}
