#include "carrent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarRent w;
    w.show();

    return a.exec();
}
