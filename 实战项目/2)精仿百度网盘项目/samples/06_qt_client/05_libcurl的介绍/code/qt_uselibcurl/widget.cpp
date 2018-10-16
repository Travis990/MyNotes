#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#include <curl/curl.h> //pro 添加 LIBS += -L/usr/local/lib -lcurl
#include <stdio.h>
#include <string.h>

char buf[1024 * 4];
int i = 0;

//此回调函数被调用的时机是有响应数据到达，这些数据由ptr指向，每次接收的数据大小是size*nmemb
static size_t callback( char *ptr, size_t size, size_t nmemb, void *stream)
{
    memcpy(buf + i, ptr, size*nmemb);
    i += size*nmemb;
    buf[i] = 0;

    return size*nmemb;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    CURL *curl = curl_easy_init();//初始化一个CURL的指针

    //设置 curl 的属性和操作
    //CURLOPT_URL：设置访问URL
    //curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/login?type=10&user=itcast&pwd=1");
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/login?type=10&user=测试&pwd=12345");

    //设置回调函数callback
    //callback将在libcurl接收到数据后被调用，因此函数多做数据保存的功能
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);


    //完成curl_easy_setopt指定的所有选项, 返回0意味一切ok，非0代表错误发生，此函数会阻塞，等待服务器返回数据
    //CURLcode res = curl_easy_perform(curl);
    curl_easy_perform(curl);
    qDebug() << "buf = " << buf;

    curl_easy_cleanup(curl);

}
