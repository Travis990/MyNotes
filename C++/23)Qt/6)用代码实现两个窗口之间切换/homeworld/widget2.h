#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>

class widget2 : public QWidget
{
    Q_OBJECT
public:
    explicit widget2(QWidget *parent = nullptr);

signals:
    //自定义信号
    void btn2func();

public slots:
};

#endif // WIDGET2_H
