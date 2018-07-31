#include "mainwindow.h"
#include<QMenuBar>//菜单的头文件
#include<QToolBar>//工具的头文件
#include<QStatusBar>//状态栏的头文件
#include<QLabel>//标签的头文件
#include<QDockWidget>//停靠部件的头文件
#include<QTextEdit>//编辑框的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(800,600);
    //添加菜单栏，菜单栏有且只有一个
    QMenuBar *mb = this->menuBar();
    //往菜单栏中添加菜单
    //创建菜单项,添加到菜单栏
    QMenu *menuFile = mb->addMenu("文件");
    QMenu *menuEdit = mb->addMenu("编辑");

    //往菜单项中添加菜单
    QAction *Qaction = menuFile->addAction("新建");
    QAction *Qaction2 = menuEdit->addAction("打开");
    //添加分割符
    menuFile->addSeparator();
    QAction *save = menuFile->addAction("保存");
    //添加二级菜单
    QMenu *menuRecet = menuFile->addMenu("最近打开的文件");
    menuRecet->addAction("1.txt");

    //工具栏
    QToolBar *toolBar = new QToolBar();
    this->addToolBar(toolBar);
    //往工具栏中添加工具
    toolBar->addAction(Qaction);
    toolBar->addAction(Qaction2);
    //运行工具栏只停靠在左边和右边
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
    //不让工具栏浮动
    toolBar->setFloatable(false);
    //不让工具栏移动
    toolBar->setMovable(false);

    //状态栏
    QStatusBar *sta = this->statusBar();
    QLabel *label = new QLabel("左侧布局",this);
    sta->addWidget(label);
    QLabel *label2 = new QLabel("右侧布局",this);
    //sta->addWidget(label2);
    //标签在状态栏的右边
    sta->addPermanentWidget(label2);

    //停靠部件
    QDockWidget *dw = new QDockWidget("停靠部件",this);
    //将停靠部件添加到窗口上，停靠在底部
    //注意停靠部件需要一个参照物,一般这个参照物就核心部件
    this->addDockWidget(Qt::BottomDockWidgetArea,dw);

    //创建编辑框
    QTextEdit *text = new QTextEdit(this);
    //设置编辑框为核心部件
    setCentralWidget(text);
}

MainWindow::~MainWindow()
{

}
