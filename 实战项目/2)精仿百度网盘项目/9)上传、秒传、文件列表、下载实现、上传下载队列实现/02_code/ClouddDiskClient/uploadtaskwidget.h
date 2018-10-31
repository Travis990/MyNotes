#ifndef UPLOADTASKWIDGET_H
#define UPLOADTASKWIDGET_H

#include <QWidget>
#include "transfertaskwidget.h"

class UploadTaskWidget : public TransferTaskWidget
{
    Q_OBJECT
public:
    explicit UploadTaskWidget(QWidget *parent = nullptr);
    UploadTaskWidget(QString localFile , QString remoteFile, QWidget *parent = nullptr);

signals:
    void transferFinished(QString log);

public slots:
};

#endif // UPLOADTASKWIDGET_H
