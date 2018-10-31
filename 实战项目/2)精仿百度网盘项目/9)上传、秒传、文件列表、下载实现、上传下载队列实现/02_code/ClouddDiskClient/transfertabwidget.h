#ifndef TRANSFERTABWIDGET_H
#define TRANSFERTABWIDGET_H

#include <QWidget>

namespace Ui {
class TransferTabWidget;
}

class TransferTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransferTabWidget(QWidget *parent = 0);
    ~TransferTabWidget();
    void appendUploadTask(QString localFile , QString remoteFile);

private:
    Ui::TransferTabWidget *ui;
};

#endif // TRANSFERTABWIDGET_H
