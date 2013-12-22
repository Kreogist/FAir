#ifndef AIRBASE_H
#define AIRBASE_H

#include <QMainWindow>
#include"QDebug"
#include"TcpConnection.h"
#include"QSettings"
#include"QDir"
namespace Ui {
class AirBase;
}

class AirBase : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AirBase(QWidget *parent = 0);
    ~AirBase();
    
private slots:
    void on_upload_clicked();
    void on_connect_clicked();

    void on_sync_clicked();

private:
    Ui::AirBase *ui;
    void createSyncFile();
    QSettings *airSetting;
    TcpConnection *CtS;

signals:
    void FStartSender();
};

#endif // AIRBASE_H
