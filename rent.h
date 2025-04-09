#ifndef RENT_H
#define RENT_H

#include <QString>

class Rent
{
public:
    Rent();
    Rent(int rid,
         int bid,
         int cid,
         QString fio,
         uint startts,
         uint endts,
         bool finished);
    int rid;
    int bid;
    int cid;
    QString fio;
    uint startts;
    uint endts;
    bool finished;
};

#endif // RENT_H
