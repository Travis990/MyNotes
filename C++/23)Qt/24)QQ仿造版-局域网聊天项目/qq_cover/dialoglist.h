#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>
#include<QVector>
#include<QToolButton>
#include "widget.h"

namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = 0);
    ~DialogList();

    void CreaToolButton();

    //关联按键和聊天窗口
    void BtnByWindow();

private:
    Ui::DialogList *ui;

    QVector<QToolButton*> vToolBtn;

    //标记窗口是否弹出
    QVector<bool> isShow;
};


#endif // DIALOGLIST_H
