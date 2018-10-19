#include "user.h"

User::User()
{

}

QString User::userName() const
{
    return mUserName;
}

void User::setUserName(const QString &userName)
{
    mUserName = userName;
}

QString User::passwd() const
{
    return mPasswd;
}

void User::setPasswd(const QString &passwd)
{
    mPasswd = passwd;
}

QString User::nickName() const
{
    return mNickName;
}

void User::setNickName(const QString &nickName)
{
    mNickName = nickName;
}

QString User::phone() const
{
    return mPhone;
}

void User::setPhone(const QString &phone)
{
    mPhone = phone;
}

QString User::email() const
{
    return mEmail;
}

void User::setEmail(const QString &email)
{
    mEmail = email;
}

QString User::token() const
{
    return mToken;
}

void User::setToken(const QString &token)
{
    mToken = token;
}

User& User::loginUser()
{
    return mLoginUser;
}

User User::mLoginUser;
