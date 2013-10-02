#ifndef FDOWNLOADER_H
#define FDOWNLOADER_H

#include"QNetworkAccessManager"
#include"QByteArray"
#include"QString"
#include"QUrl"
#include"QObject"
#include"QFileInfo"
#include"QMessageBox"
#include"QFile"
#include"QNetworkReply"
#include"QVariant"
#include"QDebug"
class FDownloader : public QObject
{
    Q_OBJECT
private :
    QNetworkAccessManager *downloader;
    QFile *file;
    QNetworkReply *reply;
    bool httpRequestAborted;
    QNetworkAccessManager qnam;
    QUrl url;
public:
    void download(QUrl url);
    void startRequest(QUrl url);
    FDownloader();
private slots:
    void httpFinished();
    void httpReadyRead();
    //void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
};

#endif // FDOWNLOADER_H
