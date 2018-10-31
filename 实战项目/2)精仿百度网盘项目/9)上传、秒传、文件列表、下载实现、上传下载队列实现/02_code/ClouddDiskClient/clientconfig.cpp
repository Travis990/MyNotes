#include "clientconfig.h"
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>

//单例
ClientConfig ClientConfig::smInstance;

ClientConfig::ClientConfig()
{
    QFileInfo fileInfo(CLIENT_CONFIG_FILE_NAME);
    if(!fileInfo.exists()||!fileInfo.isFile())
    {
        return;
    }
    QFile file(CLIENT_CONFIG_FILE_NAME);
    file.open(QIODevice::ReadOnly);
    QByteArray content = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(content);
    if(doc.isObject())
    {
        QJsonObject obj = doc.object();
        if(obj.value("ip").isString())
        {
            this->setIp(obj.value("ip").toString());
        }
        if(obj.value("port").isString())
        {
            this->setPort(obj.value("port").toString());
        }
        if(obj.value("userName").isString())
        {
            this->setUserName(obj.value("userName").toString());
        }
        if(obj.value("passwd").isString())
        {
            this->setPasswd(obj.value("passwd").toString());
            this->setPasswd(QByteArray::fromBase64( this->passwd().toUtf8()));
        }
        if(obj.value("rememberPasswd").isBool())
        {
            this->setIsRememberPasswd(obj.value("rememberPasswd").toBool());
        }
    }
    file.close();
}

bool ClientConfig::isRememberPasswd() const
{
    return mIsRememberPasswd;
}

void ClientConfig::setIsRememberPasswd(bool isRememberPasswd)
{
    mIsRememberPasswd = isRememberPasswd;
}

QString ClientConfig::passwd() const
{
    return mPasswd;
}

void ClientConfig::setPasswd(const QString &passwd)
{
    mPasswd = passwd;
}

QString ClientConfig::userName() const
{
    return mUserName;
}

void ClientConfig::setUserName(const QString &userName)
{
    mUserName = userName;
}

ClientConfig &ClientConfig::getInstance()
{
    return smInstance;
}

void ClientConfig::save()
{
    QFileInfo fileInfo(CLIENT_CONFIG_FILE_NAME);
    if(fileInfo.exists()&&!fileInfo.isFile())
    {
        //如果文件名存在并且不是文件而是其他（比如目录，那么就不操作）
        return;
    }
    QFile file(CLIENT_CONFIG_FILE_NAME);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QByteArray content = file.readAll();
    QJsonObject obj;
    obj.insert("ip",this->ip());
    obj.insert("port",this->port());
    obj.insert("userName",this->userName());
    obj.insert("rememberPasswd",this->isRememberPasswd());
    if(this->isRememberPasswd())
    {
        obj.insert("passwd",QString(this->passwd().toUtf8().toBase64()));
    }

    QJsonDocument doc(obj);
    file.write(doc.toJson());
    file.close();
}

QString ClientConfig::ip() const
{
    return mIp;
}

void ClientConfig::setIp(const QString &ip)
{
    mIp = ip;
}

QString ClientConfig::port() const
{
    return mPort;
}

void ClientConfig::setPort(const QString &port)
{
    mPort = port;
}
