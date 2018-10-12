#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QHostInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Http 协议");
    setWindowIcon(QIcon(":/favicon.ico"));

    pserver = NULL;

    pserver = new QTcpServer(this);
    // 初始化IP和端口
    ui->port->setText("30000");
    ui->port->setAlignment(Qt::AlignHCenter);
    ui->btnClose->setEnabled(false);
    // ip address
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> AddressList = info.addresses();
    AddressList.append(QHostAddress(quint32(0)));
    foreach(QHostAddress address, AddressList)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress::Null && address != QHostAddress::LocalHost)
        {
            ui->address->addItem(address.toString());
        }
    }

    // 判断有无连接请求
    connect(pserver, &QTcpServer::newConnection, [=]()
    {
        // 接受连接请求
        QTcpSocket *pconn = pserver->nextPendingConnection();
        if(!list.contains(pconn))
        {
            list.append(pconn);
            //当有数据到达的时候就读取
            connect(pconn, &QTcpSocket::readyRead, this, [=]()
            {
                QByteArray all = pconn->readAll();
                QColor color(qrand()%255, qrand()%255, qrand()%255);
                ui->httpData->setTextColor(color);
                ui->httpData->append("************ IP: " + pconn->peerAddress().toString() + " ************");
                ui->httpData->append("************ Port: " + QString::number(pconn->peerPort()) + " ************");
                ui->httpData->append(all);
            });
        }
    });

    // 启动服务器
    connect(ui->btnStart, &QPushButton::clicked, [=]()
    {
        // port
        int port = ui->port->text().toInt();

        // 设置监听
        pserver->listen(QHostAddress(ui->address->currentText()), port);
        // 按钮状态
        ui->btnClose->setEnabled(true);
        ui->btnStart->setEnabled(false);
        ui->address->setEnabled(false);
        ui->port->setEnabled(false);
    });
    // 关闭服务器
    connect(ui->btnClose, &QPushButton::clicked, this, [=]()
    {
        ui->btnClose->setEnabled(false);
        ui->btnStart->setEnabled(true);
        ui->address->setEnabled(true);
        ui->port->setEnabled(true);

        pserver->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
