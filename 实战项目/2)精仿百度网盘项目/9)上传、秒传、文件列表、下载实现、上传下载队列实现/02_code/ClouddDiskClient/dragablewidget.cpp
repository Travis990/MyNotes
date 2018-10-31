#include "dragablewidget.h"

DragableWidget::DragableWidget(QWidget *parent) : QWidget(parent)
{

}

void DragableWidget::mousePressEvent(QMouseEvent *ev)
{
    // 如果是左键, 计算窗口左上角, 和当前按钮位置的距离
    if(ev->button() == Qt::LeftButton)
    {
        // 计算和窗口左上角的相对位置
        m_pos = ev->globalPos() - this->parentWidget()->geometry().topLeft();
    }
}

void DragableWidget::mouseMoveEvent(QMouseEvent *ev)
{
    // 移动是持续的状态, 需要使用buttons
    if(ev->buttons() & Qt::LeftButton)
    {
        QPoint pos = ev->globalPos() - m_pos;
        this->parentWidget()->move(pos);
    }
}
