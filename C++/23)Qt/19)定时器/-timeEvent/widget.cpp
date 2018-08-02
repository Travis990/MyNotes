#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    timeId=0;
    timeId2=0;
    ui->setupUi(this);

//    startTimer(1000);//表示1秒调用一下timeEvent函数

}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    //qDebug()<<"主人，该上课了";
    if(timeId==event->timerId())
    {
        //第一个定时器
        static int num=1;
        ui->lcdNumber->display(num++);
    }

    if(timeId2==event->timerId())
    {
        //第二个定时器
        static int num=1;
        ui->lcdNumber_2->display(num++);
    }


}

void Widget::on_pushButton_start_clicked()
{
    timeId=startTimer(1000);
}

void Widget::on_pushButton_stop_clicked()
{
    //停止定时器
    killTimer(timeId);
}

void Widget::on_pushButton_start_2_clicked()
{
    timeId2=startTimer(100);
}

void Widget::on_pushButton_stop_2_clicked()
{
    //停止定时器
    killTimer(timeId2);
}

void Widget::on_pushButton_start3_clicked()
{
    timer=new QTimer(this);
    //启动定时器
    timer->start(10);
    connect(timer,&QTimer::timeout,[=](){
        static int num=1;
        ui->lcdNumber_3->display(num++);
    });
}

void Widget::on_pushButton_stop3_clicked()
{
    timer->stop();
}
