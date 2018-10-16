#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager> //pro需要添加 QT += network
#include <QNetworkReply>
#include <QList>
#include <QFile>
#include <QTimer>   //定时器，取下载队列的信息

//下载文件信息
struct DownloadInfo
{
    QUrl url;    //下载网址
    QFile *file; //文件指针
    QString fileName; //文件名字
    bool isRun; //是否已经在下载
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void appendDownloadList( QUrl url); //追加任务到下载队列

private slots:
    void on_pushButton_clicked();
    void slotTimeout(); //定时器槽函数

private:
    Ui::Widget *ui;

    //QNetworkAccessManager类允许应用程序发送网络请求和接收网络应答。
    QNetworkAccessManager *manager;

    //下载队列
    QList<DownloadInfo *> list;

    QTimer timer; //定时器对象

};

#endif // WIDGET_H
