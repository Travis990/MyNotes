#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>
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

void Widget::on_pushButton_clicked()
{
    //QString to QUrl
    //获取编辑区内容
    QUrl url = ui->lineEdit->text();
    cout << "url.path() = " << url.path();

    //获取文件名
    QString fileName( QFileInfo( url.path() ).fileName() );
    cout << "fileName = " << fileName;

    if(fileName.isEmpty()) //如果文件名为空
    {
        cout << "fileName.isEmpty()";
        return;
    }

    QFile *file = new QFile(fileName); //文件指针分配空间

    if(!file->open(QIODevice::WriteOnly))
    { //如果打开文件失败，则删除 file，并使 file 指针为 0，然后返回
        cout << "file open error";

        delete file;
        file = NULL;
        return;
    }

     //发送get请求
    QNetworkReply * reply = manager->get( QNetworkRequest(url) );
    if(reply == NULL)
    {
        cout << "reply is NULL";
        return;
    }

    //设置进度条值为0
    ui->progressBar->setValue(0);

    //Lambda表达式， 配置文件添加： CONFIG += c++11

    //关联信号和槽
    //获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished,
        [=]() mutable
        {
            //关闭文件
            if(file->isOpen())
            {
                file->close();
            }

            reply->deleteLater();

            reply = NULL;
            delete file;
            file = NULL;
        }
    );


    //当有可用数据时，reply 就会发出readyRead()信号，我们这时就可以将可用的数据保存下来
    connect(reply, &QNetworkReply::readyRead,
        [=]()
        {
            //如果文件存在，则写入文件
            if (file != NULL)
            {
                file->write(reply->readAll());
            }
        }
    );

    //有可用数据更新时
    connect(reply, &QNetworkReply::downloadProgress,
        [=](qint64 bytesRead, qint64 totalBytes)
        {
            ui->progressBar->setMaximum(totalBytes); //最大值
            ui->progressBar->setValue(bytesRead);    //当前值
        }
    );

}
