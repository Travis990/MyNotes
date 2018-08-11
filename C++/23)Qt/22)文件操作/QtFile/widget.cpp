#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QFile>
#include<QTextCodec>//编码的头文件
#include<QFileInfo>//获取文件信息的头文件
#include<QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //获取文件路径
    QString strpath = "D:\\github\\mynotes\\C++\\23)Qt\\22)文件操作\\txt\\长恨歌_utf-8.txt";

    QFileInfo info(strpath);
    QDateTime fileCdate = info.created();
    QString Cdate = "文件创建的日期:";
    Cdate += fileCdate.toString("yyyy-MM-dd h:m:s");

    QString Xdate = "文件修改的日期:";
    Xdate += info.lastModified().toString("yyyy-MM-dd h:m:s");

    QFile file("D:\\github\\mynotes\\C++\\23)Qt\\22)文件操作\\txt\\fileinfo.txt");
    file.open(QIODevice::WriteOnly| QIODevice::Append);

    file.write(Cdate.toUtf8());
    file.write("\r\n");
    file.write(Xdate.toUtf8());
    file.close();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString filepath;
    filepath = QFileDialog::getOpenFileName(this,"打开一个文件",
                                            "D:\\github\\mynotes\\C++\\23)Qt\\22)文件操作\\txt",
                                            "TXT(*.txt)"
                                            );
    ui->lineEdit->setText(filepath);

    //判断用户是否选择了文件
    if(filepath.isEmpty())
    {
        return;
    }

    //开始读取文件
    /*
    // 1.一次性读取全部内容
    //创建文件对象
    QFile file(filepath);
    //打开文件,只读方式
    file.open(QIODevice::ReadOnly);
    //读取文件的全部内容
    QByteArray conter=file.readAll();
    //默认显示utf-8格式
    ui->plainTextEdit->setPlainText(conter);
    //关闭文件
    file.close();
*/

    /*
    // 2.一行一行读取
    //创建文件对象
    QFile file(filepath);
    //打开文件,只读方式
    file.open(QIODevice::ReadOnly);
    QByteArray conter;
    do
    {
        conter+=file.readLine();

    }while (!file.atEnd());//判断是否读取到文件尾部

    //默认显示utf-8格式
    ui->plainTextEdit->setPlainText(conter);

    //关闭文件
    file.close();
*/

    // 3.读取gbk格式的文件
    //一行一行读取
    //创建文件对象
    QFile file(filepath);
    //打开文件,只读方式
    file.open(QIODevice::ReadOnly);
    QByteArray conter;
    do
    {
        conter+=file.readLine();

    }while (!file.atEnd());//判断是否读取到文件尾部
    QTextCodec *code=QTextCodec::codecForName("GBK");
    QString str=code->toUnicode(conter);

    ui->plainTextEdit->setPlainText(str);


    //关闭文件
    file.close();
}
