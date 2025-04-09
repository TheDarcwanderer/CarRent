#ifndef CARPARK_H
#define CARPARK_H

#include <QString>

class CarPark
{
public:
    CarPark();
    CarPark(int pid, QString name);
    int pid;
    QString name;
};

#endif // CARPARK_H
