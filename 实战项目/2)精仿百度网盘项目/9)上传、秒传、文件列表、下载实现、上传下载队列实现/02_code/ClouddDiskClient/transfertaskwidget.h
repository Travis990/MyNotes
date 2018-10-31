#ifndef TRANSFERTASKWIDGET_H
#define TRANSFERTASKWIDGET_H

#include <QWidget>

namespace Ui {
class TransferTaskWidget;
}

class TransferTaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransferTaskWidget(QWidget *parent = 0);
    ~TransferTaskWidget();

    Ui::TransferTaskWidget *ui;
private:
};

#endif // TRANSFERTASKWIDGET_H
