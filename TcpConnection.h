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
    void updateClientProgress(qint64); //发送数据，更新进度条
    void displayError(QAbstractSocket::SocketError); //显示错误

private :
    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据


};

#endif // TCPCONNECTION_H
