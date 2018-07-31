#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>//1.引入头文件

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mybutton(QPushButton *parent = nullptr);
    //alt+回车
    ~mybutton();
signals:

public slots:
};

#endif // MYBUTTON_H
