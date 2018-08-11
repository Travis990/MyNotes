#include "widget.h"
#include "ui_widget.h"
#include<QDataStream>//数据流的头文件
#include<QMessageBox>
#include<QDateTime>
#include<QColorDialog>//颜色的头文件
#include<QFileDialog>//文件对话框

Widget::Widget(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->uName = name;

    port = 23333;

    udpSocket = new QUdpSocket(this);
    //ShareAddress模式表示允许其他的服务连接到相同的地址和端口
    //ReuseAddressHint 断开重新连接
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    //点击发送按键发送消息
    connect(ui->sendBtn,&QPushButton::clicked,this,[=](){
        //发送消息
        sendMsg(Msg);
    });

    //监听信号，当数据传输成功，会触发readyRead
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReveMessage);
    //有新用户加入
    sendMsg(UsrEnter);

    //点击退出按键
    connect(ui->exitBtn,&QPushButton::clicked,this,[=](){
        //会触发CloseEvent函数
        this->close();
    });

    setButtonfunc();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMsg(Widget::MsgType type)
{
    //数据流中的数据共三段，消息类型+用户名+具体内容
    QByteArray data;//存储数据
    //把out中的数据存储到data
    QDataStream out(&data, QIODevice::WriteOnly);
    //将消息和用户名放入到数据流中
    out<<type<<getUsr();

    switch (type) {
    case Msg:
        if(ui->msgTxtEdit->toPlainText() == "")
        {
            QMessageBox::warning(0,"警告","发送的内容不能为空",QMessageBox::Ok);
            return;
        }
        //把具体的内容放入到流中
        out<<getMsg();
        break;
    case UsrEnter:
        //用户登入
        //因为前面把消息类型和用户名已经放入到数据流中，
        //所以这里不需要放入数据
        break;
    default:
        break;
    }

    //发送数据流
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
}


void Widget::ReveMessage()
{
    QByteArray dataram;
    //开辟空间
    dataram.resize(udpSocket->pendingDatagramSize());
    //获取内容
    udpSocket->readDatagram(dataram.data(),dataram.size());
    //解析数据
    //第一端是消息类型，第二段是用户名，第三段是具体内容
    QDataStream in(&dataram,QIODevice::ReadOnly);
    int msgType;
    in>>msgType;//获取用户的消息类型
    QString usrName,msg;//用户名和具体内容

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (msgType) {
    case Msg:
        in>>usrName>>msg;
        //设置颜色
        ui->msgBrowser->setTextColor(Qt::blue);
        //设置字体大小
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman",12));
        //名字加时间
        ui->msgBrowser->append("["+usrName+"]"+time);
        //追加内容
        ui->msgBrowser->append(msg);
        break;
    case UsrEnter:
        in>>usrName;//从数据流中获取用户名
        usrEnter(usrName);
        break;
    case UsrLeft:
        in>>usrName;
        usrLeft(usrName,time);
        break;
    default:
        break;
    }
}

QString Widget::getUsr()
{
    return this->uName;
}

QString Widget::getMsg()
{
    //获取输入框的内容
    QString msg = ui->msgTxtEdit->toHtml();
    //清空输入框的内容
    ui->msgTxtEdit->clear();
    //关标再次聚焦到输入框
    ui->msgTxtEdit->setFocus();
    return msg;
}

void Widget::usrEnter(QString username)
{
    //查询usrTblWidget中有没有这个用户，如果没有返回真
    bool isEmpty = ui->usrTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *usr = new QTableWidgetItem(username);
        //插入行
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0,0,usr);

        //设置字体属性
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));

        ui->msgBrowser->append(tr("%1 在线").arg(username));
        ui->usrNumLbl->setText(tr("在线人数:%1").arg(ui->usrTblWidget->rowCount()));
        sendMsg(UsrEnter);
    }
}

void Widget::usrLeft(QString username, QString time)
{
    //查询usrTblWidget中有没有这个用户，如果没有返回真
    bool isEmpty = ui->usrTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(!isEmpty)
    {
        //获取这个用户在第几行
        int rowNum = ui->usrTblWidget->findItems(username,Qt::MatchExactly).first()->row();
        ui->usrTblWidget->removeRow(rowNum);

        //设置字体属性
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));

        ui->msgBrowser->append(QString("%1 于 %2 离开").arg(username).arg(time));
        ui->usrNumLbl->setText(tr("在线人数:%1").arg(ui->usrTblWidget->rowCount()));
    }
}

void Widget::setButtonfunc()
{
    //字体设置
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,this,[=](const QFont &f){
        ui->msgTxtEdit->setCurrentFont(f);
        ui->msgTxtEdit->setFocus();
    });

    //字号设置
    void (QComboBox::*CbxS)(const QString &text) = &QComboBox::currentIndexChanged;
    connect(ui->sizeCbx,CbxS,this,[=](const QString &text){
        ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();
    });

    //加粗
    connect(ui->boldTBtn,&QToolButton::clicked,this,[=](bool checked){
        if(checked)
        {
            ui->msgTxtEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTxtEdit->setFontWeight(QFont::Normal);
        }
        ui->msgTxtEdit->setFocus();
    });

    //倾斜
    connect(ui->italicTBtn,&QToolButton::clicked,this,[=](bool checked){
        ui->msgTxtEdit->setFontItalic(checked);
        ui->msgTxtEdit->setFocus();
    });

    //下划线
    connect(ui->underlineTBtn,&QToolButton::clicked,this,[=](bool checked){
        ui->msgTxtEdit->setFontUnderline(checked);
        ui->msgTxtEdit->setFocus();
    });

    //设置颜色
    connect(ui->colorTBtn,&QToolButton::clicked,this,[=](){
        QColor color = QColorDialog::getColor(Qt::red);
        if(color.isValid())
        {
            ui->msgTxtEdit->setTextColor(color);
            ui->msgTxtEdit->setFocus();
        }
    });

    //清空聊天记录
    connect(ui->clearTBtn,&QToolButton::clicked,this,[=](){
        ui->msgTxtEdit->clear();
    });

    //保存聊天记录
    connect(ui->saveTBtn,&QToolButton::clicked,this,[=](){
        QString fileName = QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
        if(!fileName.isEmpty())
        {
            //保存名称不为空再做保存操作
            QFile file(fileName);
            file.open(QIODevice::WriteOnly| QIODevice::Text);
            QTextStream stream(&file);
            //获取显示框中所有的内容
            stream<<ui->msgBrowser->toPlainText();
            file.close();
        }
    });
}

void Widget::closeEvent(QCloseEvent *event)
{
    emit this->windowClose();

    sendMsg(UsrLeft);

    udpSocket->close();
    udpSocket->destroyed();

    QWidget::closeEvent(event);
}

