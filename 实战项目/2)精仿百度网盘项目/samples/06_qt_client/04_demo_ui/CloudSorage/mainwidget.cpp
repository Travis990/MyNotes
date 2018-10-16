#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "common.h"
#include <QPainter>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

     //自定义窗口标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);

    //信号和槽连接函数
    deal_connect();
}

//信号和槽连接函数
void MainWidget::deal_connect()
{
    //信号和槽连接
    //信号 ---> 信号
    //主窗口关闭，发送信号告诉登陆窗口，登陆窗口也关闭
    connect(ui->mainButton, &MainWidgetButton::buttonCloseSignal,
        this, &MainWidget::mainWidgetCloseSignal);

    //最大化按钮处理
    connect(ui->mainButton, &MainWidgetButton::buttonMaxSignal,
    [=]() mutable
    {
        if(this->isMaximized() == false) //如果不是最大化显示
        {
            this->showMaximized(); //最大化显示
        }
        else//如果已经最大化显示，再按，则正常模式显示
        {
            this->showNormal(); //正常显示
        }

    }
    );

    //最小化按钮处理
    connect(ui->mainButton, &MainWidgetButton::buttonMinSignal, this, &MainWidget::showMinimized);

    //我的文件按钮
    connect(ui->mainButton, &MainWidgetButton::buttonMyFilesSignal,
    [=]() mutable
    {
        cout << "我的文件";
    }
    );

    //共享列表按钮
    connect(ui->mainButton, &MainWidgetButton::buttonShareFilesSignal,
    [=]() mutable
    {
        cout << "共享列表";
    }
    );

    //共享文件下载榜按钮
    connect(ui->mainButton, &MainWidgetButton::buttonRankingListSignal,
    [=]() mutable
    {
        cout << "共享文件下载榜";
    }
    );

    //传输列表按钮
    connect(ui->mainButton, &MainWidgetButton::buttonDataSignal,
    [=]() mutable
    {
        cout << "传输列表按钮";
    }
    );

    //切换用户按钮
    connect(ui->mainButton, &MainWidgetButton::buttonChangeSignal,
    [=]() mutable
    {
        cout << "切换用户按钮";
    }
    );
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)//绘图事件，画背景图
{
    QPainter p(this);
    //设置反走样，反走样的效果比不走样要好些
    //p.setRenderHint(QPainter::Antialiasing);
    p.drawPixmap(this->rect(), QPixmap(":/image/display_bk.bmp"));
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        //如果是右键
        //close();
    }
    else if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
       move(e->globalPos() - p);
    }
}

//显示主界面窗口
void MainWidget::showMainWidget()
{
    moveToCenter(this); //居中显示
}
