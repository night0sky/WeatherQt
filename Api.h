#ifndef API_H
#define API_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class ApiCaller : public QObject
{
    Q_OBJECT
public:
    explicit ApiCaller(QObject *parent = nullptr);
    ~ApiCaller();

    void sendGetRequest(const QUrl &url);
    void sendPostRequest(const QUrl &url, const QByteArray &postData);

    QString LocationID;

signals:
    void requestCompleted(const QByteArray &data);
    void requestFailed(const QString &error);

private slots:
    void handleReply(QNetworkReply* data);

private:
    QNetworkAccessManager *manager;
};

#endif // API_H
