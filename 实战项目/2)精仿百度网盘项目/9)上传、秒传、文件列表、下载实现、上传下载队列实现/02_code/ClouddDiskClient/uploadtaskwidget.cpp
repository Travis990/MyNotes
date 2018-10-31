#include "uploadtaskwidget.h"
#include "networkmanager.h"
#include "user.h"
#include <QNetworkReply>
#include "ui_transfertaskwidget.h"

UploadTaskWidget::UploadTaskWidget(QWidget *parent) : TransferTaskWidget(parent)
{

}


UploadTaskWidget::UploadTaskWidget(QString localFile , QString remoteFile, QWidget *parent)
    : TransferTaskWidget(parent)
{
    QNetworkReply *rpl =NetworkManager::getInstance().postFile("upload",User::loginUser().token(),localFile,remoteFile);
    this->ui->label_task_name->setText(remoteFile);
    this->ui->label_task_status->setText("传输中...");
    connect(rpl,&QNetworkReply::finished,[=](){
        this->ui->label_task_status->setText("传输完成");
        emit this->transferFinished("上传成功");
        rpl->deleteLater();
    });

    connect(rpl,&QNetworkReply::uploadProgress,[=](qint64 bytesSent, qint64 bytesTotal){
        this->ui->progressBar->setMaximum(bytesTotal);
        this->ui->progressBar->setValue(bytesSent);
    });
}
