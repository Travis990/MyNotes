#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    this->setStyleSheet("QPushButton{"
//                        "color:red;"
//                    "}");
}

Widget::~Widget()
{
    delete ui;
}
