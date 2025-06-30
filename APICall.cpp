#include "Api.h"

ApiCaller::ApiCaller(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

ApiCaller::~ApiCaller(){

}


void ApiCaller::sendGetRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply);
    });
}

void ApiCaller::sendPostRequest(const QUrl &url, const QByteArray &postData)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply);
    });
}

void ApiCaller::handleReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit requestCompleted(data);
    } else {
        emit requestFailed(reply->errorString());
    }
    reply->deleteLater();
}
