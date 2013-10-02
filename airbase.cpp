#include "airbase.h"
#include "ui_airbase.h"
#include"QDebug"
#include"QFileDialog"
#include"fdownloader.h"
AirBase::AirBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirBase)
{
    ui->setupUi(this);
}

AirBase::~AirBase()
{
    delete ui;
}

void AirBase::on_upload_clicked()
{
    qDebug()<<"ss";
}

void AirBase::on_pushButton_clicked()
{
    FDownloader *downloader=new FDownloader();
    downloader->download(QUrl(ui->urlipt->text()));
}
