#include "airbase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setApplicationName("FAir");
    qApp->setApplicationVersion("0.0.0.1");

    AirBase w;
    w.show();
    
    return a.exec();
}
