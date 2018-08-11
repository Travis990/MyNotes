#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle("客户端");

    setFixedSize(400,400);

    tcpSocket = new QTcpSocket(this);

    //如果连接成功,触发connected信号
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        ui->textEdit->setText("成功和服务器建立连接");
    });

    //如果对方发送数据成功
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //从通信套接字中获取内容
        QByteArray array = tcpSocket->readAll();
        //把内容设置到编辑框
        ui->textEdit->append(array);
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

// 连接按键的槽函数
void ClientWidget::on_pushButton_clicked()
{
    //获取用户输入的ip和端口号
    QString ip = ui->lineEdit_2->text();
    qint16 port = ui->lineEdit->text().toInt();

    //主动和服务器连接
    tcpSocket->connectToHost(ip,port);
}

// 发送按键的槽函数
void ClientWidget::on_pushButton_2_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //获取编辑框的内容
    QString str = ui->textEdit_2->toPlainText();

    tcpSocket->write(str.toUtf8().data());
}

// 关闭按键的槽函数
void ClientWidget::on_pushButton_3_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }

    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket = NULL;
}
