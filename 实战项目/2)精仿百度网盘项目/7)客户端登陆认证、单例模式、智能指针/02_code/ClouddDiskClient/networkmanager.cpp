#include "networkmanager.h"
#include <QJsonDocument>

NetworkManager NetworkManager::smInstance;

NetworkManager::NetworkManager(QObject *parent) : QNetworkAccessManager(parent)
{

}

NetworkManager &NetworkManager::getInstance()
{
    return smInstance;
}

QNetworkReply *NetworkManager::postObject(QString url, QVariant obj)
{
    QJsonDocument doc = QJsonDocument::fromVariant(obj);
    QByteArray json = doc.toJson();

    //3 发送http请求
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    //设置为json的 Content-type
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    return this->post(req,json);
}
