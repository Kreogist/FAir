#ifndef FREGISTER_H
#define FREGISTER_H

#include <QMainWindow>
#include "QFile"
namespace Ui {
class Fregister;
}

class Fregister : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fregister(QWidget *parent = 0);
    ~Fregister();

private slots:
    void on_regist_clicked();

private:
    Ui::Fregister *ui;
};

#endif // FREGISTER_H
