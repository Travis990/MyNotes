#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPixmap>//位图头文件头

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    //创建位图对象
    QPixmap pix(":/Image/Luffy.png");
    //画家画图片
    pa.drawPixmap(x,0,pix);
}

void Widget::on_pushButton_clicked()
{
    x += 10;
    if(x > 200)
    {
        x = 0;
    }

    //第一种方法:手动触发绘图事件
    //repaint();
    //第二种方法:有优化，如果调用10多次update函数，
    //最终只会触发最后一次绘图事件
    update();
}
