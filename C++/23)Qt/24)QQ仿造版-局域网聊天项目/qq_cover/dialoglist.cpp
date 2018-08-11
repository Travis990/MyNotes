#include "dialoglist.h"
#include "ui_dialoglist.h"
#include<QMessageBox>

DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    setWindowTitle("QQ10");
    //设置标题图片
    setWindowIcon(QIcon(":/images/qq.png"));

    //创建头像按键
    CreaToolButton();
    //关联按键和聊天窗口
    BtnByWindow();

    //设置标志位为false
    for(int i=0;i<8;i++)
    {
        isShow.push_back(false);
    }
}

DialogList::~DialogList()
{
    delete ui;
}

void DialogList::CreaToolButton()
{
    QList<QString>nameList;
    nameList << "水票奇缘" << "忆梦如澜" <<"北京出版人"<<"Cherry"<<"淡然"
             <<"娇娇girl"<<"落水无痕"<<"青墨暖暖";


    QStringList iconNameList; //图标资源列表
    iconNameList << "spqy"<< "ymrl" <<"qq" <<"Cherry"<< "dr"
                 <<"jj"<<"lswh"<<"qmnn";

    for(int i = 0; i < 8;i++)
    {
        //创建新的按键
        QToolButton *btn = new QToolButton;
        btn->setText(nameList.at(i));
        QString iconNameIcon = QString(":/images/%1.png").arg(iconNameList.at(i));
        //设置按键的大小
        btn->setFixedSize(230,70);
        //设置图片
        btn->setIcon(QPixmap(iconNameIcon));
        //设置图片大小
        btn->setIconSize(QPixmap(iconNameIcon).size());
        //设置图片的透明度
        btn->setAutoRaise(true);
        //设置按键的风格，可以同时显示图片和文字
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //将9个按键放入
        ui->formLayout->addWidget(btn);

        //将9个按键放入vector
        vToolBtn.push_back(btn);
    }
}

void DialogList::BtnByWindow()
{
    //添加事件
    for(int i = 0; i<vToolBtn.size();i++)
    {
        connect(vToolBtn.at(i),&QToolButton::clicked,[=](){
            if(isShow.at(i))
            {
                //如果进来，表示这个窗口已经弹出
                QMessageBox::warning(this,"警告",QString("用户%1已经打开")
                                     .arg(vToolBtn[i]->text()));
                return;
            }
            isShow[i] = true;
            //第一个参数是0，代表这个窗口是顶层窗口，第二个参数表示告诉窗口，按键的人物姓名
            Widget *chatwidget = new Widget(0,vToolBtn.at(i)->text());
            //设置窗口的标题
            chatwidget->setWindowTitle(vToolBtn.at(i)->text());
            //设置窗口的图片
            chatwidget->setWindowIcon(vToolBtn.at(i)->icon());
            chatwidget->show();

            connect(chatwidget,&Widget::windowClose,this,[=](){
                isShow[i] = false;
            });
        });
    }
}
