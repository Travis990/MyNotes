#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

#include <QFile>
#include <QFileInfo>
#include <QTime>
#include <QNetworkReply>
#include <QHttpPart>
#include <QMimeDatabase>
#include <QMessageBox>

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

//产生分隔线
QString Widget::getBoundary()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //随机种子
    QString tmp;

    // 48~122, '0'~'A'~'z'
    for(int i = 0; i < 16; i++)
    {
        tmp[i] = qrand() % (122-48) + 48;
    }
    //cout << "tmp = " << tmp;

    return QString("------WebKitFormBoundary%1").arg(tmp);
}

//按钮槽函数
void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "打开文件");

    if(path.isEmpty())
    {
        cout << "path.isEmpty()";
        return;
    }

    //获取文件属性信息
    QFileInfo info(path);
    //获取文件大小，返回bytes
    if(info.size() > 30*1024*1024) //最大文件只能是30M
    {
        cout << "file is to big\n";
        return;
    }

    //获取文件名
    QString fileName = info.fileName();
    cout << "fileName = " << fileName;

    QFile file(path); //创建文件对象

    if( !file.open(QIODevice::QIODevice::ReadOnly) )
    { //如果打开文件失败，则删除 file，并使 file 指针为 0，然后返回
        cout << "file open error";
        return;
    }

     /*
    ------WebKitFormBoundary88asdgewtgewx\r\n
    Content-Disposition: form-data; user="itcast"; filename="xxx.jpg"; token="xxxx"; size=10240\r\n
    Content-Type: image/png\r\n
    \r\n
    真正的文件内容\r\n
    ------WebKitFormBoundary88asdgewtgewx
    */

    QString boundary = getBoundary(); //产生分隔线

    QByteArray data;

    //第1行，分隔线
    data.append(boundary);
    data.append("\r\n");

    //上传文件信息
    data.append("Content-Disposition: form-data; ");
    data.append( QString("token=\"%1\" ").arg( "b6dc7a1386174e7c2c05b39252f74323" ) ); //上传用户
    data.append( QString("filename=\"%1\" ").arg(fileName) ); //文件名字
    data.append("\r\n");


    //自动根据文件类型来算出数据的MIME类型，比如text/plain  application/json
    QMimeType mimeType = QMimeDatabase().mimeTypeForFile(fileName);
    data.append("Content-Type: ");
    data.append(mimeType.name());
    data.append("\r\n");
    data.append("\r\n");

    //上传文件内容
    data.append( file.readAll() ); //文件内容
    data.append("\r\n");

    //结束分隔线
    data.append(boundary);

    file.close(); //关闭文件


    QNetworkRequest request; //请求对象
    request.setUrl(QUrl( ui->lineEdit->text() )); //设置url

    //qt默认的请求头
    //request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/multi");

    //发送post请求
    QNetworkReply * reply = manager->post( request, data );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    ui->progressBar->setValue(0); //进度条当前值设置为0

    //有可用数据更新时
    connect(reply, &QNetworkReply::uploadProgress,
        [=](qint64 bytesRead, qint64 totalBytes)
        {
            if(totalBytes != 0) //这个条件很重要
            {
                ui->progressBar->setMaximum(totalBytes); //最大值
                ui->progressBar->setValue(bytesRead);    //当前值
            }

        }
    );

    //获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished,
        [=]()
        {
            if (reply->error() != QNetworkReply::NoError) //有错误
            {
                cout << reply->errorString();
                reply->deleteLater(); //释放资源
                return;
            }


            QByteArray array = reply->readAll();
            cout << "array = " << array.data();
            reply->deleteLater();
        }
    );

}

void Widget::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "打开文件");

    if(path.isEmpty())
    {
        cout << "path.isEmpty()";
        return;
    }

    //获取文件属性信息
    QFileInfo info(path);
    //获取文件大小，返回bytes
    if(info.size() > 30*1024*1024) //最大文件只能是30M
    {
        cout << "file is to big\n";
        return;
    }

    //获取文件名
    QString fileName = info.fileName();
    cout << "fileName = " << fileName;
    //打开文件
    QFile *file = new QFile(path);
    if(!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"错误","文件打开失败");
        delete file;
        return;
    }


    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    //自动根据文件类型来算出数据的MIME类型，比如text/plain  application/json
    //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QMimeDatabase mimeDb;
    QMimeType mimeType = mimeDb.mimeTypeForFile(path);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, mimeType.name());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data;token=\"%1\";filename=\"%2\"")
                        .arg("b6dc7a1386174e7c2c05b39252f74323")
                        .arg(fileName));
    filePart.setBodyDevice(file);
    multiPart->append(filePart);

    //文件添加父节点，自动释放
    file->setParent(multiPart);

    QNetworkRequest request; //请求对象
    request.setUrl(QUrl( ui->lineEdit_2->text() )); //设置url

    //qt默认的请求头
    //request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data");

    //发送post请求
    QNetworkReply * reply = manager->post(request,multiPart);
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    ui->progressBar_2->setValue(0); //进度条当前值设置为0

    //有可用数据更新时
    connect(reply, &QNetworkReply::uploadProgress,
        [=](qint64 bytesRead, qint64 totalBytes)
        {
            if(totalBytes != 0) //这个条件很重要
            {
                ui->progressBar_2->setMaximum(totalBytes); //最大值
                ui->progressBar_2->setValue(bytesRead);    //当前值
            }

        }
    );

    //获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished,
        [=]()
        {
            if (reply->error() != QNetworkReply::NoError) //有错误
            {
                cout << reply->errorString();
                reply->deleteLater(); //释放资源
                return;
            }


            QByteArray array = reply->readAll();
            cout << "array = " << array.data();
            reply->deleteLater();
        }
    );

}
