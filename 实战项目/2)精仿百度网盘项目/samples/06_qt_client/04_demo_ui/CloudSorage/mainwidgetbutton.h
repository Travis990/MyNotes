#ifndef MAINWIDGETBUTTON_H
#define MAINWIDGETBUTTON_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class MainWidgetButton;
}

class MainWidgetButton : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetButton(QWidget *parent = 0);
    ~MainWidgetButton();

    void setUserText(QString str);//设置用户按钮的文本
    QString getUserText();        //获取用户按钮的文本

protected:
    void paintEvent(QPaintEvent *); //绘图事件，画背景图

signals:
    void buttonCloseSignal();//关闭窗口信号
    void buttonMaxSignal();  //最大化窗口信号
    void buttonMinSignal();  //最小化窗口信号
    void buttonMyFilesSignal();     //我的文件按钮信号
    void buttonShareFilesSignal();  //共享文件列表按钮信号
    void buttonRankingListSignal(); //文件下载榜按钮信号
    void buttonDataSignal();        //传输列表按钮按钮
    void buttonChangeSignal();      //切换用户按钮信号


private slots:
    void on_buttonClose_clicked();  //关闭窗口按钮
    void on_buttonMax_clicked();    //最大化窗口按钮
    void on_buttonMin_clicked();    //最小化窗口按钮
    void on_buttonUser_clicked();   //登陆用户按钮
    void on_buttonMyFiles_clicked();//我的文件按钮
    void on_buttonShareFiles_clicked(); //共享文件列表按钮
    void on_buttonRankingList_clicked();//文件下载榜按钮
    void on_buttonData_clicked();       //传输列表按钮
    void on_buttonChange_clicked();     //切换用户按钮

private:
    Ui::MainWidgetButton *ui;
};

#endif // MAINWIDGETBUTTON_H
