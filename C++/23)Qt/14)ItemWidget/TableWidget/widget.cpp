#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //指定3列
    ui->tableWidget->setColumnCount(3);
    //指定5行
    ui->tableWidget->setRowCount(5);
    //指定表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"英雄"<<"性别"<<"年龄");
    //添加数据
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
    //使用for循环的方式添加信息
    QStringList heroNames=QStringList()<<"亚瑟"<<"小悟空"<<"赵云"<<"马云";
    QStringList heroGenders=QStringList()<<"男"<<"男"<<"男"<<"男";
    for(int row = 0; row<4; ++row)
    {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(heroNames[row]));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(heroGenders[row]));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(19+row)));
    }
}

Widget::~Widget()
{
    delete ui;
}
