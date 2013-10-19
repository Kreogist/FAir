#ifndef AIRBASE_H
#define AIRBASE_H

#include <QMainWindow>
#include"QTcpSocket"
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
#include"QHostAddress"


namespace Ui {
class AirBase;
}

class AirBase : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AirBase(QWidget *parent = 0);
    void download(QUrl url);
    void startRequest(QUrl url);
    void startTransfer(QString fileName);  //发送文件大小等信息
    ~AirBase();
    
private slots:

    void updateClientProgress(qint64); //发送数据，更新进度条
    void displayError(QAbstractSocket::SocketError); //显示错误

    void on_upload_clicked();

    void on_connect_clicked();

private:
    Ui::AirBase *ui;
    QTcpSocket *tcpClient;
    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    //QString fileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据


signals:
    void FStartSender();
};

#endif // AIRBASE_H
