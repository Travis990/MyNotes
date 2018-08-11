#include "widget.h"
#include "ui_widget.h"
#include<QPainter>//画家的头文件
#include<QPen>//画笔的头文件
#include<QBrush>//画刷的头文件

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

void Widget::paintEvent(QPaintEvent *event)
{
    //创建画笔
    QPen pen;
    //设置画笔的颜色
    pen.setColor(QColor(255,0,0));
    //设置画笔的宽度
    pen.setWidth(3);
    //设置画笔的风格
    pen.setStyle(Qt::DashLine);

    //创建画刷
    QBrush bru;
    //设置画刷的颜色
    bru.setColor(Qt::cyan);
    //设置画刷的风格
    bru.setStyle(Qt::Dense1Pattern);



    //创建画家,自动黑色画笔
    QPainter pa(this);

    //让画家拿起画笔
    pa.setPen(pen);
    //让画家拿起画刷
    pa.setBrush(bru);
    //画线
    pa.drawLine(0,0,100,100);
    //画矩形,左上角的坐标，后面两个参数是长和宽
    pa.drawRect(20,20,50,50);
    //画圆,第一个参数是圆心，第二个参数是x轴的长度，第三个参数是y轴的长度
    pa.drawEllipse(QPoint(100,100),50,50);

    //画文字
    pa.drawText(200,100,"努力敲码，将来拿高薪");
}
