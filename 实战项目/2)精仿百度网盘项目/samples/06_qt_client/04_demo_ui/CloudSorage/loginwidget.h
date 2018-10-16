#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include "mainwidget.h" //主界面，显示用户文件列表

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

protected:
    void paintEvent(QPaintEvent *);         //绘图事件，画背景图
    void mousePressEvent(QMouseEvent *e);   //鼠标点击，获取点击坐标，处理移动
    void mouseMoveEvent(QMouseEvent *e);    //鼠标移动，移动窗口

private slots:
    void on_closeButton_clicked();  //登陆界面关闭按钮
    void on_minButton_clicked();    //最小化按钮
    void on_settingsButton_clicked(); //切换到设置界面的按钮
    void on_loginRegButton_clicked(); //切换到注册界面的按钮
    void on_loginSureButton_clicked();//确定登陆按钮
    void on_setSureButton_clicked();  //确定设置的按钮
    void on_regButton_clicked();      //注册界面的确定注册按钮

private:
    Ui::LoginWidget *ui;
    QPoint p; //处理窗口移动需要使用到的坐标

    MainWidget *mainWidget;//主界面，显示用户文件列表
};

#endif // LOGINWIDGET_H
