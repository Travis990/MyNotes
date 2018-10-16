#include "mainwidgetbutton.h"
#include "ui_mainwidgetbutton.h"
#include <QPainter>
#include <QMessageBox>

MainWidgetButton::MainWidgetButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidgetButton)
{
    ui->setupUi(this);
}

MainWidgetButton::~MainWidgetButton()
{
    delete ui;
}

void MainWidgetButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //设置反走样，反走样的效果比不走样要好些
    //p.setRenderHint(QPainter::Antialiasing);
    p.drawPixmap(this->rect(), QPixmap(":/image/title_bk2.jpg"));
}

//关闭窗口按钮
void MainWidgetButton::on_buttonClose_clicked()
{
    emit this->buttonCloseSignal();
}

//最大化窗口按钮
void MainWidgetButton::on_buttonMax_clicked()
{
    emit this->buttonMaxSignal();
}

//最小化窗口按钮
void MainWidgetButton::on_buttonMin_clicked()
{
    emit this->buttonMinSignal();  //最小化窗口信号
}

//设置用户
void MainWidgetButton::setUserText(QString str)
{
    ui->buttonUser->setText(str);
}

//获取用户
QString MainWidgetButton::getUserText()
{
    return ui->buttonUser->text();
}

//登陆用户按钮
void MainWidgetButton::on_buttonUser_clicked()
{
     QMessageBox::about(this, "登陆用户", "当前登陆用户为：" + getUserText() );
}

//我的文件按钮
void MainWidgetButton::on_buttonMyFiles_clicked()
{
    emit this->buttonMyFilesSignal();
}

//共享文件列表按钮
void MainWidgetButton::on_buttonShareFiles_clicked()
{
    emit this->buttonShareFilesSignal();
}

//文件下载榜按钮
void MainWidgetButton::on_buttonRankingList_clicked()
{
    emit this->buttonRankingListSignal();
}

//传输列表按钮
void MainWidgetButton::on_buttonData_clicked()
{
    emit this->buttonDataSignal();
}

//切换用户按钮
void MainWidgetButton::on_buttonChange_clicked()
{
    emit this->buttonChangeSignal();
}
