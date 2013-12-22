#include "airbase.h"
#include "ui_airbase.h"
#include"Fregister.h"


AirBase::AirBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirBase)
{

    airSetting=new QSettings("conf.ini",QSettings::IniFormat);

    ui->setupUi(this);

    if(airSetting->value("firstLaunch").isNull())
    {
        airSetting->setValue("Path",QFileDialog::getExistingDirectory());
        airSetting->setValue("firstLaunch","false");
        Fregister *a=new Fregister();
        a->show();
    }

    CtS=new TcpConnection(this);

    CtS->tcpClient = new QTcpSocket(this);
    //connect(CtS->tcpClient,SIGNAL(bytesWritten(qint64)),CtS,SLOT(updateClientProgress(qint64)));
    connect(CtS->tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),CtS,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(CtS->tcpClient,SIGNAL(readyRead()),CtS,SLOT(reciveData()));
    //在这里添加下载文件的信号槽,在TcpConnection里实现
}

AirBase::~AirBase()
{
    delete ui;
}

void AirBase::on_upload_clicked()
{
    CtS->startUpload(QFileDialog::getOpenFileName(this));
}

void AirBase::on_connect_clicked()
{
    ui->hostLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("6666");
    CtS->tcpClient->connectToHost(QHostAddress(ui->hostLineEdit->text()),ui->portLineEdit->text().toInt());//连接
    CtS->startUpload("./userDiscern");
}

void AirBase::on_sync_clicked()
{
    createSyncFile();
    CtS->startUpload("./temp/sync");
}

void AirBase::createSyncFile()
{
    QString fileSysPath=airSetting->value("Path").toString();
    QDir systemWatcher(fileSysPath);
    QStringList fileSysDir=systemWatcher.entryList();
    QFile fileMaker("./temp/sync");
    fileMaker.open(QIODevice::ReadWrite);
    for(int i=0;i<fileSysDir.size();i++)
    {
        fileMaker.write(fileSysDir[i].toStdString().c_str(),fileSysDir[i].size());
        fileMaker.write("\n",1);
    }
    fileMaker.close();
}
