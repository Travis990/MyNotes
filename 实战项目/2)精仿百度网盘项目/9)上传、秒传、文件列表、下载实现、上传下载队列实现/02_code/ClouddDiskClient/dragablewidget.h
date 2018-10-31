#ifndef DRAGABLEWIDGET_H
#define DRAGABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class DragableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragableWidget(QWidget *parent = nullptr);
protected:

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:

public slots:
private:
    QPoint m_pos;        // 保存鼠标按下时的坐标
};

#endif // DRAGABLEWIDGET_H
