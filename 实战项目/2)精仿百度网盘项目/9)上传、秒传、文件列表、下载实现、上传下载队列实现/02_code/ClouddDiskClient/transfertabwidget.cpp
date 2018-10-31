#include "transfertabwidget.h"
#include "ui_transfertabwidget.h"
#include "transfertaskwidget.h"
#include "networkmanager.h"
#include <QNetworkReply>
#include "user.h"
#include "ui_transfertaskwidget.h"
#include "uploadtaskwidget.h"

TransferTabWidget::TransferTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransferTabWidget)
{
    ui->setupUi(this);
}

TransferTabWidget::~TransferTabWidget()
{
    delete ui;
}

void TransferTabWidget::appendUploadTask(QString localFile, QString remoteFile)
{
    //往上传队列里边添加一个任务
    auto task = new UploadTaskWidget(localFile,remoteFile,this);
    this->ui->verticalLayout_upload_queue->insertWidget(0,task); //往上传队列的layout插入一个控件
    connect(task,&UploadTaskWidget::transferFinished,[=](QString log){
        //根据上传的结果将日志放到listWidget
        this->ui->listWidget_transfer_log->addItem(log);
    });

}
