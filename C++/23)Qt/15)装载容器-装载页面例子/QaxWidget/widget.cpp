#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //添加浏览器的id
    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    //设置默认打开的网页
    QString webstr = QString("www.baidu.com");
    ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);
}

Widget::~Widget()
{
    delete ui;
}
