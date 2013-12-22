#include "Fregister.h"
#include "ui_Fregister.h"

Fregister::Fregister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fregister)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
}

Fregister::~Fregister()
{
    delete ui;
}

void Fregister::on_regist_clicked()
{
    QString uid,pw;
    QFile user("./userDiscern");
    uid=ui->id->text();
    pw=ui->password->text();
    user.open(QIODevice::ReadWrite);
    user.write(uid.toLocal8Bit(),uid.size());
    user.write("\n",1);
    user.write(pw.toLocal8Bit(),pw.size());
    user.close();
}
