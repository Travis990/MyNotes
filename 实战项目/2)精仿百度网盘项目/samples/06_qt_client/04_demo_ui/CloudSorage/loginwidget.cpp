#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QPainter>

#include "common.h"
#include <QJsonDocument>    //QJsonDocument要求使用 Qt5, pro文件：QT  += core
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "logininfoinstance.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    //去窗口表框
    setWindowFlags(Qt::FramelessWindowHint);

    //居中显示窗口
    moveToCenter(this); //common.h中实现此函数

    //登陆界面
    ui->stackedWidget->setCurrentWidget(ui->pageLogin);
    //注册界面
    //ui->stackedWidget->setCurrentWidget(ui->pageRegister);
    //设置界面
    //ui->stackedWidget->setCurrentWidget(ui->pageSettings);


    //动态分配空间，不需要指定父窗口，此界面作为单独的窗口
    mainWidget = new MainWidget;

    connect(mainWidget, &MainWidget::mainWidgetCloseSignal,
    [=]() mutable
    {
        mainWidget->close();    //主界面窗口关闭
        this->close();          //登陆窗口关闭
    }
    );
}

LoginWidget::~LoginWidget()
{
    delete mainWidget; //释放堆区空间
    delete ui;
}

//登陆界面关闭按钮
void LoginWidget::on_closeButton_clicked()
{
    if( ui->stackedWidget->currentWidget() == ui->pageLogin)
    {//如果登陆窗口，按关闭按钮，关闭整个窗口
        mainWidget->close();    //主界面窗口关闭
        this->close();          //登陆窗口关闭
    }
    else if( ui->stackedWidget->currentWidget() == ui->pageRegister )
    {//如果注册窗口，按关闭按钮，关闭本页面，切换回登陆界面
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);

        //清空行编辑内容
        ui->regUser->clear();
        ui->regNickName->clear();
        ui->regFirstPwd->clear();
        ui->regSurePwd->clear();
        ui->regPhone->clear();
        ui->regEmail->clear();
    }
    else if( ui->stackedWidget->currentWidget() == ui->pageSettings )
    {//如果设置窗口，按关闭按钮，关闭本页面，切换回登陆界面
        ui->stackedWidget->setCurrentWidget(ui->pageLogin);
    }
}

//最小化按钮
void LoginWidget::on_minButton_clicked()
{
    this->showMinimized(); //最小化显示
}

//切换到设置界面的按钮
void LoginWidget::on_settingsButton_clicked()
{
    //切换到设置界面
    ui->stackedWidget->setCurrentWidget(ui->pageSettings);
}

//切换到注册界面的按钮
void LoginWidget::on_loginRegButton_clicked()
{
    //切换到注册界面
    ui->stackedWidget->setCurrentWidget(ui->pageRegister);
}


//确定登陆按钮
void LoginWidget::on_loginSureButton_clicked()
{
    cout << "登陆按钮";

    //判断输入内容是否为空
    QString user = ui->loginUser->text();
    QString pwd = ui->loginPwd->text();

    if( user.isEmpty() || pwd.isEmpty() )
    {
        QMessageBox::warning(this, "内容不能为空", "输入内容不能为空！！！");
        return;
    }

    //设置登陆信息，显示文件列表界面需要使用这些信息
    LoginInfoInstance *p = LoginInfoInstance::getInstance(); //获取单例
    p->setLoginInfo(user, ui->serverIP->text(), ui->serverPort->text());
    cout << p->getUser().toUtf8().data() << ", " << p->getIp() << ", " << p->getPort();

    this->mainWidget->showMainWidget();//显示主界面
    this->hide(); //本窗口隐藏

}

//确定设置的按钮
void LoginWidget::on_setSureButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageLogin);
}

//注册界面的确定注册按钮
void LoginWidget::on_regButton_clicked()
{
    cout << "在注册界面的注册按钮";
}

//绘图事件，画背景图
void LoginWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //设置反走样，反走样的效果比不走样要好些
    //p.setRenderHint(QPainter::Antialiasing);
    p.drawPixmap(this->rect(), QPixmap(":/image/login_bk.jpg"));
}

//鼠标点击，获取点击坐标，处理移动
void LoginWidget::mousePressEvent(QMouseEvent *e)
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

//鼠标移动，移动窗口
void LoginWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
       move(e->globalPos() - p);
    }
}
