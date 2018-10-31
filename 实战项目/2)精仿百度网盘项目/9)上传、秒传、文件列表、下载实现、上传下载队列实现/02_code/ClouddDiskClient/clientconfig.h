#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H
#include <QString>
#define CLIENT_CONFIG_FILE_NAME "cfg.json"

class ClientConfig
{

public:
    static ClientConfig &getInstance();
    void save();

    QString ip() const;
    void setIp(const QString &ip);

    QString port() const;
    void setPort(const QString &port);

    QString userName() const;
    void setUserName(const QString &userName);

    QString passwd() const;
    void setPasswd(const QString &passwd);

    bool isRememberPasswd() const;
    void setIsRememberPasswd(bool isRememberPasswd);

private:
    ClientConfig();
    QString mIp;
    QString mPort;
    QString mUserName;
    QString mPasswd;
    bool mIsRememberPasswd;
    static ClientConfig smInstance;
};

#endif // CLIENTCONFIG_H
