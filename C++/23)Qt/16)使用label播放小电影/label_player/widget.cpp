#include "widget.h"
#include "ui_widget.h"
#include<QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //在label中播放小电影
    QMovie *movie = new QMovie(":/Image/mario.gif");
    ui->label->setMovie(movie);
    //播放电影
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}
