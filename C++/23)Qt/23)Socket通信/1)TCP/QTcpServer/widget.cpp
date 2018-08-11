#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    //创建监听套接字
    tcpServer = new QTcpServer(this);
    //监听,第一个参数表示监听网络中所有的接口，第二参数是端口号
    tcpServer->listen(QHostAddress::Any,9999);

    //设置窗口标题
    setWindowTitle("服务器:9999");

    //如果和客户端连接成功，会触发newConnection信号
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //获取通信套接字
        tcpSocket = tcpServer->nextPendingConnection();

        //通过通信套接字来获取客户端的ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();
        QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);

        //把信息设置到上面的编辑框中
        ui->textEdit->setText(temp);

        //如果对方发送信息成功，会触发readyRead
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //从通信套接字中获取内容
            QByteArray array = tcpSocket->readAll();
            //把内容设置到编辑框
            ui->textEdit->append(array);
        });
    });
}

Widget::~Widget()
{
    delete ui;
}

// 按键"发送"
void Widget::on_pushButton_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //获取编辑框的内容
    QString str = ui->textEdit_2->toPlainText();

    tcpSocket->write(str.toUtf8().data());
}

// 按键"关闭",关闭是主动和客户端断开连接
void Widget::on_pushButton_2_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }

    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket = NULL;
}
