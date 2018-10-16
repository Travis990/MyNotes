//将某个字符串加密成md5码
QString getStrMd5(QString str)
{
    QByteArray array;

    //md5加密, 所需头文件#include <QCryptographicHash>
    array = QCryptographicHash::hash ( str.toLocal8Bit(), QCryptographicHash::Md5 );

    return array.toHex() ; //返回
}