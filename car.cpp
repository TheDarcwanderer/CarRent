#include "car.h"

Car::Car(){}

Car::Car(int cid,
         int pid,
         QString fabricator,
         QString model,
         int yearOfProduction,
         QString color,
         QString number,
         QString pts,
         bool active)
{
    this->cid = cid;
    this->pid = pid;
    this->fabricator = fabricator;
    this->model = model;
    this->yearOfProduction = yearOfProduction;
    this->color = color;
    this->number = number;
    this->pts = pts;
    this->active = active;
}
