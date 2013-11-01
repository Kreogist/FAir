#include "airbase.h"
#include "ui_airbase.h"


AirBase::AirBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirBase)
{
    ui->setupUi(this);
    CtS=new TcpConnection(this);

    CtS->tcpClient = new QTcpSocket(this);
    connect(CtS->tcpClient,SIGNAL(bytesWritten(qint64)),CtS,SLOT(updateClientProgress(qint64)));
    connect(CtS->tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),CtS,SLOT(displayError(QAbstractSocket::SocketError)));
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
}
