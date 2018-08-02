#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>

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
    QMessageBox::information(this,"读取自定义控件的值",QString("%1").arg(ui->widget->getVal()));
}

void Widget::on_pushButton_2_clicked()
{
    ui->widget->setVal(50);
}
