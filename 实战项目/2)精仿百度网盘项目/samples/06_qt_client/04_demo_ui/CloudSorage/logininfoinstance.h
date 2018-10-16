#ifndef LOGININFOINSTANCE_H
#define LOGININFOINSTANCE_H

#include <QString>
#include "common.h"


//单例模式，主要保存当前登陆用户，服务器信息
class LoginInfoInstance
{
public:
     static LoginInfoInstance *getInstance(); //保证唯一一个实例
     static void destroy(); //释放堆区空间

     void setLoginInfo( QString tmpUser, QString tmpIp, QString tmpPort);//设置登陆信息
     QString getUser() const;   //获取登陆用户
     QString getIp() const;     //获取服务器ip
     QString getPort() const;   //获取服务器端口

private:
    //构造和析构函数为私有的
    LoginInfoInstance();
    ~LoginInfoInstance();

    //它的唯一工作就是在析构函数中删除Singleton的实例
    class Garbo
    {
    public:
        ~Garbo()
        {
            //释放堆区空间
            LoginInfoInstance::destroy();
        }
    };

    //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数
    //static类的析构函数在main()退出后调用
    static Garbo tmp; //静态数据成员，类中声明，类外定义


    //静态数据成员，类中声明，类外必须定义
    static LoginInfoInstance *instance;


    QString user;   //当前登陆用户
    QString ip;     //web服务器ip
    QString port;   //web服务器端口
};

#endif // LOGININFOINSTANCE_H
