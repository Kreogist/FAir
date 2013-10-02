#include "airbase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AirBase w;
    w.show();
    
    return a.exec();
}
