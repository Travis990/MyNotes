#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager> //pro需要添加 QT += network
#include <QNetworkReply>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //设置登陆用户信息的json包
    QByteArray setLoginJson(QString user, QString pwd);

private slots:
    void on_pushButton_clicked();

    void slotFinished(QNetworkReply*);

private:
    Ui::Widget *ui;

    //QNetworkAccessManager类允许应用程序发送网络请求和接收网络应答。
    QNetworkAccessManager *manager;
};

#endif // WIDGET_H
