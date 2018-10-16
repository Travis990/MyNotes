#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

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

    //定时器的信号和槽
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimeout()) );

    //启动定时器，200毫秒间隔
    timer.start(200);
}

Widget::~Widget()
{
    delete ui;
}

//追加任务到下载队列
void Widget::appendDownloadList( QUrl url)
{
    //遍历查看一下，下载的文件是否已经在下载队列中
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->url == url) //list[i]->url
        {
            cout << QFileInfo( url.path() ).fileName() << " 已经在下载队列中 ";
            return;
        }
    }

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

    //动态创建节点
    DownloadInfo *tmp = new DownloadInfo;
    tmp->file = file;         //文件指针
    tmp->fileName = fileName; //文件名字
    tmp->url = url;           //下载网址
    tmp->isRun = false;       //没有在下载

    //插入节点
    list.append(tmp);
}

//下载按钮
void Widget::on_pushButton_clicked()
{
    //追加任务到下载队列
    appendDownloadList(ui->lineEdit_1->text());
    appendDownloadList(ui->lineEdit_2->text());
    appendDownloadList(ui->lineEdit_3->text());
    appendDownloadList(ui->lineEdit_4->text());

}

//定时器槽函数
void Widget::slotTimeout()
{
    //如果队列为空，无需往下操作
    if(list.isEmpty())
    {
        return;
    }

    //遍历下载队列
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->isRun == true) //说明有下载任务
        {

            return;
        }
    }

    //取出第一个任务
    DownloadInfo *tmp = list.at(0);
    QUrl url = tmp->url;
    QFile *file = tmp->file;
    QString fileName = tmp->fileName;

    list.at(0)->isRun = true; //标志位，设置此文件在下载


    //发送get请求
    QNetworkReply * reply = manager->get( QNetworkRequest(url) );
    if(reply == NULL)
    {
        delete file;
        file = NULL;
        return;
    }

    ui->label->setText(fileName); //显示下载文件标示
    cout << "download file = " << fileName;
    ui->progressBar->setValue(0);

    //Lambda表达式， Qt5.6以下配置文件添加： CONFIG += c++11
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

            //遍历下载队列
            for(int i = 0; i != list.size(); ++i)
            {
                if( list.at(i)->isRun == true) //说明有下载任务
                {
                    //移除此文件，因为已经下载完成了
                    DownloadInfo *tmp = list.takeAt(i);
                    delete tmp; //释放空间
                    break;
                }
            }
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
