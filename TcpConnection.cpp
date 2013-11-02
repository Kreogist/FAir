#include "TcpConnection.h"

TcpConnection::TcpConnection(QObject *parent) :
    QObject(parent)
{
    loadSize = 4096;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
}

void TcpConnection::startUpload(QString fileName)  //实现文件大小等信息的发送
{
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFileName;

    totalBytes += outBlock.size();

    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));

    bytesToWrite = totalBytes - tcpClient->write(outBlock);

    outBlock.resize(0);
}

void TcpConnection::updateClientProgress(qint64 numBytes) //更新进度条，实现文件的传送
{
    bytesWritten += (int)numBytes;

    if(bytesToWrite > 0)
    {
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));
        bytesToWrite -= (int)tcpClient->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        localFile->close();
    }

    if(bytesWritten == totalBytes) //发送完毕
    {
        qDebug()<<"传送文件成功";
        localFile->close();
        delete localFile;
    }
}

void TcpConnection::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    //ui->clientProgressBar->reset();
}

void TcpConnection::reciveData()  //更新进度条，接收数据
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_6);

    if(bytesReceived <= sizeof(qint64)*2)
    {

        if((tcpClient->bytesAvailable() >= sizeof(qint64)*2)&& (fileNameSize == 0))
        {
            in >> DownloadtotalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }

        if((tcpClient->bytesAvailable() >= fileNameSize)
                && (fileNameSize != 0))
        {
            in >> fileName;
            bytesReceived += fileNameSize;
            DownloadlocalFile = new QFile(fileName);
            if(!DownloadlocalFile->open(QFile::WriteOnly))
            {
                qDebug() << "open file error!";
                return;
            }
        }

        else return;
    }


    if(bytesReceived < totalBytes)
    {
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    if(bytesReceived == totalBytes)
    {
        DownloadlocalFile->close();
        delete DownloadlocalFile;
        totalBytes = 0;
        bytesReceived = 0;
        fileNameSize = 0;
    }
}
