#ifndef AIRBASE_H
#define AIRBASE_H

#include <QMainWindow>
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

    void on_pushButton_clicked();

private:
    Ui::AirBase *ui;
};

#endif // AIRBASE_H
