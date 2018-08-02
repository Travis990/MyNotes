#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QListWidgetItem *item = new QListWidgetItem("床前明月光");
    //设置文字的位置，1表示在左边，2表示在右边，4表示在中间
    item->setTextAlignment(2);
    ui->listWidget->addItem(item);

    //一次性写入多行文字
    QStringList strlist;
    strlist<<"疑是地上霜"<<"举头望明月"<<"低头思故乡";
    ui->listWidget->addItems(strlist);
}

Widget::~Widget()
{
    delete ui;
}
