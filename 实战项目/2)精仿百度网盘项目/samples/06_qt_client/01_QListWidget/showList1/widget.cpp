#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMenu>

#include <QDebug>
#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] " //没有分号

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->listWidget->setViewMode(QListView::IconMode);   //设置显示图标模式
    ui->listWidget->setIconSize(QSize(80, 80));         //设置图标大小
    ui->listWidget->setGridSize(QSize(100, 120));        //设置item大小

    //设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
    ui->listWidget->setResizeMode(QListView::Adjust);   //自动适应布局

    //设置列表可以拖动，如果想固定不能拖动，使用QListView::Static
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setSpacing(30); //设置图标之间的间距, 当setGridSize()时，此选项无效
    ui->listWidget->setContextMenuPolicy( Qt::CustomContextMenu );


    //添加项目
    ui->listWidget->addItem(new QListWidgetItem(QIcon("../file_png/jpg.png"), "1.jpg"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("../file_png/png.png"), "2.png"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("../file_png/mpeg.png"), "测试很长的名字.mp4"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("../file_png/tar.png"), "4.tar"));

    //clearItems();//清空item项目

    //上传文件
    ui->listWidget->addItem(new QListWidgetItem(QIcon("../file_png/upload.png"), "上传文件"));


    //单击item时，触发itemClicked信号
    connect(ui->listWidget, &QListWidget::itemClicked,
        [=](QListWidgetItem *item) mutable //参数为当前选中的item
        {
            QString text = item->text(); //获取item的文字
            cout << "text = " << text.toStdString().data();

            if(text == "上传文件") //上传文件，弹出选择文件对话框
            {
                QStringList list = QFileDialog::getOpenFileNames();
                for(int i = 0; i < list.size(); ++i)
                {
                    cout << "所选文件为："<<list.at(i);
                }
            }
        }

    );

    //=====================================菜单1
    menuItem = new QMenu( this );

     //动作1
    downloadAction = new QAction("下载",this);
    shareAction = new QAction("分享",this);
    propertyAction = new QAction("属性",this);

    //动作1添加到菜单1
    menuItem->addAction(downloadAction);
    menuItem->addAction(shareAction);
    menuItem->addAction(propertyAction);

    //======================================菜单2
    menuEmpty = new QMenu( this );


    //动作2
    refreshAction = new QAction("刷新",this);
    uploadAction = new QAction("上传",this);

    //动作2添加到菜单2
    menuEmpty->addAction(refreshAction);
    menuEmpty->addAction(uploadAction);

    //========================================信号与槽
    connect(downloadAction, &QAction::triggered,
        [=]() mutable   //下载
        {
            cout << "下载动作";
        }

    );

    connect(shareAction, &QAction::triggered,
        [=]() mutable   //分享
        {
            cout << "分享动作";
        }

    );

    connect(propertyAction, &QAction::triggered,
        [=]() mutable   //属性
        {
            cout << "属性动作";
        }

    );

    connect(refreshAction, &QAction::triggered,
        [=]() mutable   //刷新
        {
            cout << "刷新动作";
        }

    );

    connect(uploadAction, &QAction::triggered,
        [=]() mutable   //上传
        {
            cout << "上传动作";
        }

    );
}

Widget::~Widget()
{
    clearItems();//清空item项目
    delete ui;
}

void Widget::clearItems()//清空item项目
{
    //移除项目
    //使用QListWidget::count()来统计ListWidget中总共的item数目
    int n = ui->listWidget->count();
    for(int i = 0; i < n; ++i)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0); //这里是0，不是i
        delete item;
    }
}

//菜单执行
//鼠标右键信号触发 customContextMenuRequested
void Widget::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt( pos );

    if( item == NULL ) //没有点图标
    {
        //QPoint QMouseEvent::pos()   这个只是返回相对这个widget(重载了QMouseEvent的widget)的位置。
        //QPoint QMouseEvent::globalPos()  窗口坐标，这个是返回鼠标的全局坐标
        //QPoint QCursor::pos() [static] 返回相对显示器的全局坐标
        //QWidget::pos() : QPoint 这个属性获得的是当前目前控件在父窗口中的位置
        menuEmpty->exec( QCursor::pos() ); //在鼠标点击的地方弹出菜单
    }
    else //点图标
    {
        ui->listWidget->setCurrentItem(item);

        if(item->text() == "上传文件") //如果是上传文件，没有右击菜单
        {
            return;
        }

        menuItem->exec( QCursor::pos() );
    }
}
