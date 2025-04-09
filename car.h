#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    Car();
    Car(int cid,
        int pid,
        QString fabricator,
        QString model,
        int yearOfProduction,
        QString color,
        QString number,
        QString pts,
        bool active);
    int cid;
    int pid;
    QString fabricator;
    QString model;
    int yearOfProduction;
    QString color;
    QString number;
    QString pts;
    bool active;
};

#endif // CAR_H
