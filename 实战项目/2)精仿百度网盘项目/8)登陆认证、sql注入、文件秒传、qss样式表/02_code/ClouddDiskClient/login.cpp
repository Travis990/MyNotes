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
#include <QStyleOption>
#include <QCryptographicHash>
#include "networkmanager.h"
#include <QPainter>
#include "user.h"
#include "clientconfig.h"

#define REG_USER_NAME "^\\w{5,32}$"
#define REG_PASSWD "^\\w{6,16}$"
#define REG_PHONE "^\\d{11}$"
#define REG_EMAIL "^[\\w!#$%&'*+/=?^_`{|}~-]+(?:\\.[\\w!#$%&'*+/=?^_`{|}~-]+)*@(?:[\\w](?:[\\w-]*[\\w])?\\.)+[\\w](?:[\\w-]*[\\w])?$"
//匹配 点分十进制的ipv4
#define REGEXP_IPV4  "^(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}$"
//匹配 0-65535的端口
#define REGEXP_PORT  "^([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-5]{2}[0-3][0-5])$"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
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


void Login::on_pushButton_confirm_option_clicked()
{
    //点击服务器配置确定后
      //验证ip和端口号是否符合正则表达式
      QRegExp expIp(REGEXP_IPV4);
      QRegExp expPort(REGEXP_PORT);

      //获取ip和端口
      QString ip = this->ui->lineEdit_ip->text();
      QString port = this->ui->lineEdit_port->text();

      //匹配正则，不匹配就报错
      if(!expIp.exactMatch(ip))
      {
          QMessageBox::critical(this,"输入错误","IP填写有误");
          return;
      }

      if(!expPort.exactMatch(port))
      {
          QMessageBox::critical(this,"输入错误","端口填写有误");
          return;
      }
      //验证过后，就记住ip和端口
      ClientConfig::getInstance().setIp(ip);
      ClientConfig::getInstance().setPort(port);
      ClientConfig::getInstance().save();
      //确认后跳回登录界面
      this->ui->stackedWidget->setCurrentIndex(0);
}


void Login::on_pushButton_2_clicked()
{
    //登录
    //正则验证
    QRegExp expUserName(REG_USER_NAME);
    QRegExp expPasswd(REG_PASSWD);
    QString userName = this->ui->lineEdit_login_user_name->text();
    QString passwd = this->ui->lineEdit_login_passwd->text();
    //匹配正则，不匹配就报错
//    if(!expUserName.exactMatch(userName))
//    {
//        QMessageBox::critical(this,"输入错误","用户名填写有误");
//        return;
//    }
//    //匹配正则，不匹配就报错
//    if(!expPasswd.exactMatch(passwd))
//    {
//        QMessageBox::critical(this,"输入错误","密码填写有误");
//        return;
//    }
    //保存配置
    ClientConfig::getInstance().setUserName(userName);
    ClientConfig::getInstance().setPasswd(passwd);
    ClientConfig::getInstance().setIsRememberPasswd(this->ui->checkBox_remember_passwd->isChecked());
    ClientConfig::getInstance().save();
    //发送登录请求
    //将密码转为md5
    QString passwdMd5Array;
    passwdMd5Array = QCryptographicHash::hash ( passwd.toUtf8(), QCryptographicHash::Md5 ).toHex();

    QMap<QString,QVariant> userObj;
    userObj.insert("userName",userName);
    userObj.insert("passwd",passwdMd5Array);

//===============================================================================
    QNetworkReply *reply =  NetworkManager::getInstance().postObject("login",userObj);
    connect(reply,&QNetworkReply::finished,[=](){
        //根据返回数据判断登录是否成功
        /*
         * 返回结果判断，如果是0，表示请求成功
         * 否则表示失败，失败带有错误信息msg
         *
         * {
         *      code : 0,
         *      token : "xxxxxxxx"
         *      msg :""
         * }
         *
         */
        do
        {
            //网络错误或http返回错误码
            if(reply->error()!=QNetworkReply::NoError)
            {
                QMessageBox::critical(this,"出错了",reply->errorString());
                qCritical()<<"Error in Login";
                break;
            }
            //json解析错误
            QJsonParseError error;
            QByteArray replyContent= reply->readAll();
            qDebug()<<"Login reply content : " << replyContent;
            QJsonDocument doc = QJsonDocument::fromJson(replyContent,&error);
            if(error.error!=QJsonParseError::NoError)
            {
                QMessageBox::critical(this,"解析json出错",error.errorString());
                qCritical()<<"Error in login parse json string";
                break;
            }
            //json正确解析，判断内容
            /*
             *  {
             *      code : 0,
             *      token : xxxxxxxxx
             *  }
             *
             */
            QJsonObject obj = doc.object();
            int code = obj.value("code").toInt();
            qDebug()<<"Login Get Code "<<code;
            if(code == 0)
            {
                QMessageBox::information(this,"登录成功","用户登录成功!");
                QString token = obj.value("token").toString();
                User::loginUser().setUserName(userName);
                User::loginUser().setPasswd(passwd);
                //如果token过期，可以考虑做一个功能自动登录,重新刷一个token
                User::loginUser().setToken(token);
                this->loginSucc();
                break;
            }
            else
            {
                QMessageBox::critical(this,"登录失败","请检查用户名和密码!");
                break;
            }
        }while(0);
        //延时释放对象
        reply->deleteLater();
    });
}
void Login::loginSucc()
{
    //窗口切换，到主窗口
    MainWindow *window = new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
    this->hide();

//    connect(window,&MainWindow::logout,[=](){
//        this->show();
//        window->close();
//    });
}


void Login::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
