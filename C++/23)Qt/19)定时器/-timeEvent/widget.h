#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void timerEvent(QTimerEvent *event);

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_start_2_clicked();

    void on_pushButton_stop_2_clicked();

    void on_pushButton_start3_clicked();

    void on_pushButton_stop3_clicked();

private:
    Ui::Widget *ui;
    int timeId;
    int timeId2;
    QTimer *timer;
};

#endif // WIDGET_H
