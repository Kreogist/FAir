#include "airbase.h"
#include "ui_airbase.h"
#include"QDebug"
#include"QFileDialog"
AirBase::AirBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirBase)
{
    ui->setupUi(this);


    tcpClient = new QTcpSocket(this);
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    ui->hostLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("6666");
    tcpClient->connectToHost(QHostAddress(ui->hostLineEdit->text()),ui->portLineEdit->text().toInt());//连接
}

AirBase::~AirBase()
{
    delete ui;
}

void AirBase::on_upload_clicked()
{
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    //Init

    startTransfer(QFileDialog::getOpenFileName(this));
}

void AirBase::startTransfer(QString fileName)  //实现文件大小等信息的发送
{
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    totalBytes = localFile->size();
    //文件总大小
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFileName;
    //依次写入总大小信息空间，文件名大小信息空间，文件名---仅是文件名不含路径，没必要含路径

    totalBytes += outBlock.size();
    //这里的总大小是文件名大小等信息和实际文件大小的总和

    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));
    //totalBytes是文件总大小，即两个quint64的大小+文件名+文件实际内容的大小

    bytesToWrite = totalBytes - tcpClient->write(outBlock);
    //发送完头数据后剩余数据的大小，即文件实际内容的大小

    //ui->clientStatusLabel->setText(tr("已连接"));
    outBlock.resize(0);
}

void AirBase::updateClientProgress(qint64 numBytes) //更新进度条，实现文件的传送
{
    bytesWritten += (int)numBytes;
    //已经发送数据的大小
    if(bytesToWrite > 0) //如果已经发送了数据
    {
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));
      //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
      //就发送剩余数据的大小
        bytesToWrite -= (int)tcpClient->write(outBlock);
       //发送完一次数据后还剩余数据的大小
        outBlock.resize(0);
       //清空发送缓冲区
    }
    else
    {
        localFile->close(); //如果没有发送任何数据，则关闭文件
    }

    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);
    //更新进度条

    if(bytesWritten == totalBytes) //发送完毕
    {
        qDebug()<<"传送文件成功";
        localFile->close();
        delete localFile;
        //不关连接因为要准备传送下一个文件
    }
}

void AirBase::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    ui->clientProgressBar->reset();
}
