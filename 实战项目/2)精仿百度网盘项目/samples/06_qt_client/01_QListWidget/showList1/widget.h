#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void clearItems();//清空item项目

private slots:
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Widget *ui;

    QMenu *menuItem;    //菜单1
    QAction *downloadAction; //下载
    QAction *shareAction;    //分享
    QAction *propertyAction; //属性

    QMenu *menuEmpty;    //菜单2
    QAction *refreshAction; //刷新
    QAction *uploadAction;  //上传
};

#endif // WIDGET_H
