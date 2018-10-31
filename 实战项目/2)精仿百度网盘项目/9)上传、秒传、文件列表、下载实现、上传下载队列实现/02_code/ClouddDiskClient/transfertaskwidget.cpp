#include "transfertaskwidget.h"
#include "ui_transfertaskwidget.h"

TransferTaskWidget::TransferTaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransferTaskWidget)
{
    ui->setupUi(this);
}

TransferTaskWidget::~TransferTaskWidget()
{
    delete ui;
}
