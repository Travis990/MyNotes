#include "login.h"
#include "ui_login.h"
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCryptographicHash>
#include "networkmanager.h"

#define REG_USER_NAME "^\\w{5,32}$"
#define REG_PASSWD "^\\w{6,16}$"
#define REG_PHONE "^\\d{11}$"
#define REG_EMAIL "^[\\w!#$%&'*+/=?^_`{|}~-]+(?:\\.[\\w!#$%&'*+/=?^_`{|}~-]+)*@(?:[\\w](?:[\\w-]*[\\w])?\\.)+[\\w](?:[\\w-]*[\\w])?$"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::on_pushButton_goto_register_clicked()
{
    //点击设置按钮，跳到注册界面
    this->ui->stackedWidget->setCurrentIndex(1);
}

void Login::on_toolButton_options_clicked()
{
    //点击设置按钮，跳到服务器设置界面
    this->ui->stackedWidget->setCurrentIndex(2);
}

void Login::on_pushButton_back_to_login_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Login::on_pushButton_back_to_login_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Login::on_pushButton_register_clicked()
{
    //实现注册的功能
    //1 验证用户的输入数据
    QString userName = this->ui->lineEdit_user_name->text();
    QString nickName = this->ui->lineEdit_nick_name->text();
    QString passwd = this->ui->lineEdit_passwd->text();
    QString passwd2 = this->ui->lineEdit_passwd2->text();
    QString phone = this->ui->lineEdit_phone->text();
    QString email = this->ui->lineEdit_email->text();
    //验证正则
    QRegExp regName(REG_USER_NAME);
    QRegExp regPasswd(REG_PASSWD);
    QRegExp regPhone(REG_PHONE);
    QRegExp regEmail(REG_EMAIL);

    if(!regName.exactMatch(userName))
    {
        QMessageBox::critical(this,"用户名错误","用户名不符合规则");
        return;
    }
    if(!regName.exactMatch(nickName))
    {
        QMessageBox::critical(this,"昵称错误","昵称不符合规则");
        return;
    }
    if(!regPasswd.exactMatch(passwd))
    {
        QMessageBox::critical(this,"密码错误","密码不符合规则");
        return;
    }
    if(passwd!=passwd2)
    {
        QMessageBox::critical(this,"密码错误","两次输入的密码不一样");
        return;
    }
    if(!regPhone.exactMatch(phone))
    {
        QMessageBox::critical(this,"电话错误","电话不符合规则");
        return;
    }
    if(!regEmail.exactMatch(email))
    {
        QMessageBox::critical(this,"电子邮箱错误","电子邮箱不符合规则");
        return;
    }
    //密码需要使用MD5哈希
    QCryptographicHash md5(QCryptographicHash::Md5);
    //添加要计算的数据
    md5.addData(passwd.toUtf8());
    //获取md5结果
    QByteArray md5Array = md5.result();
    //最终转化为16进制字符串
    QString md5Passwd = md5Array.toHex().data();

    //2 构造json
    QMap<QString ,QVariant> obj;
    obj.insert("userName",userName);
    obj.insert("nickName",nickName);
    obj.insert("passwd",md5Passwd);
    obj.insert("phone",phone);
    obj.insert("email",email);


    QNetworkReply *rpl = NetworkManager::getInstance().postObject("http://192.168.177.170/reg",obj);
    //4 响应的处理
    connect(rpl,&QNetworkReply::finished,[=](){
        //网络判错
        do
        {
            if(rpl->error()!=QNetworkReply::NoError)
            {
                qCritical()<<"Network error:"<<rpl->errorString();
                QMessageBox::critical(this,"网络错误",rpl->errorString());
                break;
            }
            //没有网络错误,解析json数据
            QByteArray content = rpl->readAll();
            qDebug().noquote()<<"Get content:"<<content;
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(content,&err);
            if(err.error!=QJsonParseError::NoError)
            {
                //json解析出错
                qCritical()<<"Json parse error:"<<err.errorString();
                QMessageBox::critical(this,"Json解析出错",err.errorString());
                break;
            }
            //判断服务端返回值的code是否为0
            QJsonObject obj = doc.object();
            int code = obj.value("code").toInt();
            if(code==0)
            {
                //用户注册成功
                QMessageBox::information(this,"恭喜","用户注册成功");
                this->ui->stackedWidget->setCurrentIndex(0);//跳到登录界面
                break;
            }
            else if(code ==11)
            {
                //用户已存在
                QMessageBox::critical(this,"注册失败","用户已经存在");
                break;
            }
            else
            {
                //其他错误
                QMessageBox::critical(this,"注册失败","未知错误");
                break;
            }
        }while(0);

        //释放reply
        rpl->deleteLater();
    });
}












