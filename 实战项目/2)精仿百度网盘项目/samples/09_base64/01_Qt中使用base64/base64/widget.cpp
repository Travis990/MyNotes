#include "widget.h"
#include <string.h>
#include <QDebug>
#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] " //没有分号

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //base64编码
    char src[] = "我爱C语言";
    int src_len = strlen(src);
    cout << "1[我爱C语言] toBase64 = " << QByteArray(src, src_len).toBase64();

    QString str = "我爱C语言";
    QByteArray array;
    array.append(str);
    QByteArray base64 = array.toBase64();
    cout << "2[我爱C语言] toBase64 = " << base64;

    char tmp[1024] = {0};
    strcpy(tmp, base64.data());
    cout << "3[我爱C语言] toBase64 = " << tmp;

    //base64解码
    QByteArray dst = QByteArray::fromBase64( tmp );
    cout << "dst = " << dst.data();

}

Widget::~Widget()
{

}
