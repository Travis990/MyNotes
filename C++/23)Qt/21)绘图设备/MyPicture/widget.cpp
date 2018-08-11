#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPixmap>//绘图设备
#include<QImage>//绘图设备
#include<QPicture>//摄像机

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*
        //参数是图片的大小
        QPixmap pix(300,300);
        //填充白色，默认是黑色
        pix.fill(Qt::white);

        QPainter pa(&pix);
        pa.drawEllipse(QPoint(150,150),100,100);
        pix.save("E:\\QT10\\day04\\03paintDevices\\pix.png");


        QImage img(300,300,QImage::Format_RGB32);
        img.fill(Qt::white);
        QPainter pa(&img);
        pa.drawEllipse(QPoint(150,150),100,100);
        img.save("E:\\QT10\\day04\\03paintDevices\\img.png");
    */

    //创建摄像机
    QPicture pic;

    //画家拿起摄像机
    QPainter pa(&pic);
    //画家开始摄像
    pa.begin(&pic);

    pa.drawEllipse(QPoint(150,150),100,100);

    pa.end();

    pic.save(".\pic.png");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    /*
        QImage ima;
        //加载图片
        ima.load(":/Image/Luffy.png");
        //设置图片上某个区域的颜色
        for(int x=50;x<100;x++)
        {
            for(int y=50;y<100;y++)
            {
                //设置图片坐标上的像素
                ima.setPixelColor(x,y,QColor(0,255,0));
            }
        }

        QPainter pa(this);
        pa.drawImage(0,0,ima);
    */

    //重现场景
    QPicture pic;
    pic.load("./pic.png");
    QPainter pa(this);
    //画家重现记录
    pa.drawPicture(0,0,pic);
}
