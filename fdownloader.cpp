#include "fdownloader.h"

FDownloader::FDownloader()
{

}

void FDownloader::download(QUrl url)
{

    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName))
    {
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
    {
        delete file;
        file = 0;
        return;
    }

    //progressDialog->setWindowTitle(tr("HTTP"));
    //progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
    //downloadButton->setEnabled(false);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void FDownloader::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),SLOT(httpFinished()));
    connect(reply,SIGNAL(readyRead()),SLOT(httpReadyRead()));
    //QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(updateDataReadProgress(qint64,qint64)));
    //qDebug()<<reply;
}

void FDownloader::httpFinished()
{
    if (httpRequestAborted)
    {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        //progressDialog->hide();
        return;
    }

    //progressDialog->hide();
    file->flush();
    file->close();


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error())
    {
        file->remove();

    }
    else if (!redirectionTarget.isNull())
    {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());

            url = newUrl;
            reply->deleteLater();
            file->open(QIODevice::WriteOnly);
            file->resize(0);
            startRequest(url);
            return;
    }
    else
    {
        //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        //downloadButton->setEnabled(true);
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void FDownloader::httpReadyRead()
{
    if (file)
        file->write(reply->readAll());
    qDebug()<<"reading";
}
