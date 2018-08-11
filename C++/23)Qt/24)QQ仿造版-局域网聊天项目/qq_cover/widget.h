#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUdpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent,QString name);
    ~Widget();

public:
    //聊天信息，用户加入，用户退出
    enum MsgType{Msg,UsrEnter,UsrLeft};

    void sendMsg(MsgType type); //广播消息
    void ReveMessage();//接收udp传输的消息

    //获取用户名
    QString getUsr();
    //获取具体内容
    QString getMsg();
    //处理新用户进入
    void usrEnter(QString username);
    //处理用户离开
    void usrLeft(QString username,QString time);
    //设置按键的功能
    void setButtonfunc();

signals:
    void windowClose();
protected:
    //重写窗口关闭事件
    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket;
    qint16 port;//端口号
    QString uName;//用户名
};

#endif // WIDGET_H
