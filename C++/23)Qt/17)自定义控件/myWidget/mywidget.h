#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();

    int getVal(); // 获取自定义控件值
    void setVal(int); // 设置自定义控件

private:
    Ui::myWidget *ui;
};

#endif // MYWIDGET_H
