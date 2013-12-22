#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include"QTcpSocket"
#include"QByteArray"
#include"QString"
#include"QUrl"
#include"QFileDialog"
#include"QFile"
#include"QNetworkReply"
#include"QDebug"
#include"QHostAddress"

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = 0);
    QTcpSocket *tcpClient;
    void download(QUrl url);
    void startRequest(QUrl url);
    void startUpload(QString fileName);

signals:

private slots:
    //void updateClientProgress(qint64); //发送数据，更新进度条
    void displayError(QAbstractSocket::SocketError); //显示错误
    void reciveData();

private :
    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据

    qint64 DownloadtotalBytes;  //存放总大小信息
    qint64 bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *DownloadlocalFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区


};

#endif // TCPCONNECTION_H
