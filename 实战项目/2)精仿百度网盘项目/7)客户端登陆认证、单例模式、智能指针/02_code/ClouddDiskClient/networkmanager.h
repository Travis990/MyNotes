#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:

    static NetworkManager &getInstance();

    QNetworkReply *postObject(QString url, QVariant obj);

signals:

public slots:
private:
    explicit NetworkManager(QObject *parent = nullptr);
    static NetworkManager smInstance;
};

#endif // NETWORKMANAGER_H
