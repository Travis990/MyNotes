#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);

    //绑定端口
    udpSocket->bind(6666);
    setWindowTitle("端口号:6666");

    //当对方成功发送数据
    connect(udpSocket,&QUdpSocket::readyRead,[=](){
        //读取数据
        char buf[1024] = {0};
        QHostAddress cilall;//对方的地址
        quint16 port;//对方端口号

        qint64 len = udpSocket->readDatagram(buf,sizeof(buf),&cilall,&port);
        if(len>0)
        {
            //格式化:[192.168.72.66:6666] 你好
            QString str = QString("[%1:%2] %3").arg(cilall.toString())
                    .arg(port)
                    .arg(buf);
            ui->textEdit->setText(str);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

//发送按键的槽函数
void Widget::on_pushButton_clicked()
{
    //先获取用户输入的ip和端口号
    QString ip = ui->lineEdit->text();
    qint16 port = ui->lineEdit_2->text().toInt();

    //获取编辑框的内容
    QString str = ui->textEdit->toPlainText();

    //给指定的用户发送信息
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}

//关闭按键的槽函数
void Widget::on_pushButton_2_clicked()
{
    this->close();
}
