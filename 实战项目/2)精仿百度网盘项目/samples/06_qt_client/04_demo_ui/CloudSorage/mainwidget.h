#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class MainWidget;
}

//主界面
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    //显示主界面窗口
    void showMainWidget();

    //信号和槽连接函数
    void deal_connect();

signals:
    void mainWidgetCloseSignal(); //主界面窗口关闭信号

protected:
    void paintEvent(QPaintEvent *); //绘图事件，画背景图
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::MainWidget *ui;

    QPoint p; //移动窗口，保存的坐标
};

#endif // MAINWIDGET_H
