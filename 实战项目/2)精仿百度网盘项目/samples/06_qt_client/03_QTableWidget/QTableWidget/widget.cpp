#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //表头相关设置
    //设置列数, 3列：排名、文件名、下载量
    ui->tableWidget->setColumnCount(3);
    //ui->tableWidget->horizontalHeader()->setDefaultSectionSize(300); //设列的宽度

    //设置表头不可点击（默认点击后进行排序）
    ui->tableWidget->horizontalHeader()-> setSectionsClickable(false);


    //设置表头内容
    QStringList header;
    header.append("排名");
    header.append("文件名");
    header.append("下载量");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    //设置字体
    QFont font = ui->tableWidget->horizontalHeader()->font(); //获取表头原来的字体
    font.setBold(true);//字体设置粗体
    ui->tableWidget->horizontalHeader()->setFont(font);

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40); //设置处垂直方向高度
    //ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    //ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见，不自动显示行号
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置不可选择
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    //ui->tableWidget->horizontalHeader()->resizeSection(0, 150); //设置表头第一列的宽度为150
    //ui->tableWidget->horizontalHeader()->setFixedHeight(40);    //设置表头的高度

    //通过样式表，设置表头背景色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");


    //设置列宽策略，使列自适应宽度，所有列平均分来填充空白部分
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    //动态插入行， 10行
    for(int i = 0; i < 10; ++i)
    {
        int rowCount = ui->tableWidget->rowCount(); //获取表单行数
        ui->tableWidget->insertRow(rowCount); //插入新行

        //新建item
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;

        //设置字体显示风格：居中
        item1->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
        item3->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);

        //排行
        //字体大写
        QFont font;
        font.setPointSize(15); //设置字体大小
        item1->setFont( font ); //设置字体
        item1->setText(QString::number(i+1));

        //文件名
        item2->setText( QString("file%1%2%3.mp4").arg(i).arg(i).arg(i));

        //下载量
        item3->setText(QString::number(1024-i));


        //设置item
        ui->tableWidget->setItem(rowCount, 0, item1);
        ui->tableWidget->setItem(rowCount, 1, item2);
        ui->tableWidget->setItem(rowCount, 2, item3);
    }

    //循环清空行
    for(int i = 0; i < 10; ++i)
    {
        //参数为0，不是i，自动delete里面的item
        //ui->tableWidget->removeRow(0);
    }
}

Widget::~Widget()
{
    delete ui;
}
