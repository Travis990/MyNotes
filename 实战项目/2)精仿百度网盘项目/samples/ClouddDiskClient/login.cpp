#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::on_pushButton_goto_register_clicked()
{
    //点击设置按钮，跳到注册界面
    this->ui->stackedWidget->setCurrentIndex(1);
}

void Login::on_toolButton_options_clicked()
{
    //点击设置按钮，跳到服务器设置界面
    this->ui->stackedWidget->setCurrentIndex(2);
}

void Login::on_pushButton_back_to_login_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Login::on_pushButton_back_to_login_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}
