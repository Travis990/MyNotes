#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager> //pro需要添加 QT += network

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QString getBoundary(); //产生分隔线

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    //QNetworkAccessManager类允许应用程序发送网络请求和接收网络应答。
    QNetworkAccessManager *manager;


};

#endif // WIDGET_H
