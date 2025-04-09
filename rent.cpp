#include "rent.h"

Rent::Rent(){}

Rent::Rent(int rid,
           int bid,
           int cid,
           QString fio,
           uint startts,
           uint endts,
           bool finished)
{
    this->rid = rid;
    this->bid = bid;
    this->cid = cid;
    this->fio = fio;
    this->startts = startts;
    this->endts = endts;
    this->finished = finished;
}
