#include "networkmanager.h"
#include "clientconfig.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QDebug>
#include <QLoggingCategory>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QMimeDatabase>

NetworkManager NetworkManager::smInstance;

NetworkManager &NetworkManager::getInstance()
{
    return smInstance;
}
QString NetworkManager::getBoundary()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //随机种子
    QString tmp;

    // 48~122, '0'~'A'~'z'
    for(int i = 0; i < 16; i++)
    {
        tmp[i] = qrand() % (122-48) + 48;
    }
    //cout << "tmp = " << tmp;

    return QString("------WebKitFormBoundary%1").arg(tmp);
}
QNetworkReply *NetworkManager::postObject(QString urlLoc,QMap<QString, QVariant> obj)
{
    QNetworkRequest request;
    QString url = QString("http://%1:%2/%3")
            .arg(ClientConfig::getInstance().ip())
            .arg(ClientConfig::getInstance().port())
            .arg(urlLoc);
    request.setUrl(QUrl(url));
    QJsonDocument doc = QJsonDocument::fromVariant(obj);
    QByteArray json = doc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,json.size());
    qDebug()<<"NetworkManager::postObject"<<url<<json;
    return this->post(request,json);
}

QNetworkReply *NetworkManager::postFile(QString urlLoc, QString token, QString fileName,QString remoteFileName)
{
    QNetworkRequest request;
    QString url = QString("http://%1:%2/%3")
            .arg(ClientConfig::getInstance().ip())
            .arg(ClientConfig::getInstance().port())
            .arg(urlLoc);
    request.setUrl(QUrl(url));

    /*
   ------WebKitFormBoundary88asdgewtgewx\r\n
   Content-Disposition: form-data; token="xxxx"; filename="aaaaaa.txt"\r\n
   Content-Type: image/png\r\n
   \r\n
   真正的文件内容\r\n
   ------WebKitFormBoundary88asdgewtgewx
   */

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    //自动根据文件类型来算出数据的MIME类型，比如text/plain  application/json
    //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QMimeDatabase mimeDb;
    QMimeType mimeType = mimeDb.mimeTypeForFile(fileName);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, mimeType.name());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data;token=\"%1\";filename=\"%2\"")
                        .arg(token)
                        .arg(remoteFileName));
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(filePart);

    return this->post(request,multiPart);
}

NetworkManager::NetworkManager(QObject *parent) : QNetworkAccessManager(parent)
{

}
