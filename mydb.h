#ifndef MYDB_H
#define MYDB_H

#include <QString>
#include <QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include "carpark.h"
#include "car.h"
#include "rent.h"

class MyDB
{
public:
    MyDB();
    static MyDB instanse;
    bool addCar(Car *car);
    bool addRent(Rent *rent);
    bool updateCar(Car *car);
    bool updateRent(Rent *rent);
    CarPark *getCarPark(int pid);
    Car *getCar(int cid);
    Rent *getRent(int rid);
    QList<CarPark> *getCarParks();
    QList<Car> *getCar();
    int getParkIdByCar(int cid);

private:
    bool addCarpark(QString name);
};

#endif // MYDB_H
