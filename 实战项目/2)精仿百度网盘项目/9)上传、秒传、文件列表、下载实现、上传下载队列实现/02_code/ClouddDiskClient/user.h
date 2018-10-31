#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    QString userName() const;
    void setUserName(const QString &userName);

    QString passwd() const;
    void setPasswd(const QString &passwd);

    QString nickName() const;
    void setNickName(const QString &nickName);

    QString phone() const;
    void setPhone(const QString &phone);

    QString email() const;
    void setEmail(const QString &email);

    QString token() const;
    void setToken(const QString &token);

    static User& loginUser();

private:
    QString mUserName;
    QString mPasswd;
    QString mNickName;
    QString mPhone;
    QString mEmail;
    QString mToken;

    static User mLoginUser;
};

#endif // USER_H
