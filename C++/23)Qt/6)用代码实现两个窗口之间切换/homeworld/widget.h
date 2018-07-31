#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"widget2.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    widget2 w2;
};

#endif // WIDGET_H
