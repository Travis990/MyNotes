#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QWidget>
#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    static NetworkManager &getInstance();
    //QNetworkReply *get(QString url);
    QNetworkReply *postObject(QString urlLoc,QMap<QString,QVariant> obj);
    QNetworkReply *postFile(QString urlLoc,QString token,QString fileName,QString remoteFileName);
private:
    explicit NetworkManager(QObject *parent = nullptr);
    QString getBoundary();

    static NetworkManager smInstance;
signals:

public slots:
};

#endif // NETWORKMANAGER_H
