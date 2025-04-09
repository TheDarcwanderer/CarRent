#include "mydb.h"
#include <QDebug>

MyDB::MyDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(".\\rent.db");
    if (!db.open())
    {
        qDebug() << "Database error: " << db.lastError();
    }

    QSqlQuery query;
    bool result = query.exec(
        "CREATE TABLE IF NOT EXISTS carparks ("
        "pid INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "unique(name))"
    ); if (!result) qDebug() << "Database::CREATE TABLE IF NOT EXISTS carparks error: " << query.lastError().text();
    result = query.exec(
        "CREATE TABLE IF NOT EXISTS cars ("
        "cid INTEGER PRIMARY KEY AUTOINCREMENT, "
        "pid INTEGER NOT NULL, "
        "fabricator TEXT NOT NULL, "
        "model TEXT NOT NULL, "
        "year_of_production INTEGER NOT NULL, "
        "color TEXT NOT NULL, "
        "number TEXT NOT NULL UNIQUE, "
        "pts TEXT NOT NULL UNIQUE, "
        "active BOOLEAN NOT NULL)"
    ); if (!result) qDebug() << "Database::CREATE TABLE IF NOT EXISTS cars error: " << query.lastError().text();
    result = query.exec(
        "CREATE TABLE IF NOT EXISTS rent ("
        "rid INTEGER PRIMARY KEY AUTOINCREMENT, "
        "bid INTEGER NOT NULL, "
        "cid INTEGER NOT NULL, "
        "fio TEXT NOT NULL, "
        "startts INTEGER NOT NULL, "
        "endts INTEGER NOT NULL, "
        "finished BOOLEAN NOT NULL)"
    ); if (!result) qDebug() << "Database::CREATE TABLE IF NOT EXISTS rent error: " << query.lastError().text();
    addCarpark("Central");
    addCarpark("West");
}

MyDB MyDB::instanse = MyDB();

bool MyDB::addCar(Car *car)
{
    QSqlQuery query;
    query.prepare("INSERT INTO cars (pid, fabricator, model, year_of_production, color, number, pts, active) VALUES (:pid, :fabricator, :model, :year_of_production, :color, :number, :pts, :active)");
    query.bindValue(":pid", car->pid);
    query.bindValue(":fabricator", car->fabricator);
    query.bindValue(":model", car->model);
    query.bindValue(":year_of_production", car->yearOfProduction);
    query.bindValue(":color", car->color);
    query.bindValue(":number", car->number);
    query.bindValue(":pts", car->pts);
    query.bindValue(":active", car->active);
    if (!query.exec())
    {
        qDebug() << "Database::addCar error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MyDB::updateCar(Car *car)
{
    QSqlQuery query;
    query.prepare("UPDATE cars SET pid=:pid, fabricator=:fbct, model=:mdl, year_of_production=:yofp, "
                  "color=:clr, number=:nbm, pts=:pts, active=:act WHERE cid=:cid");
    query.bindValue(":pid", car->pid);
    query.bindValue(":fbct", car->fabricator);
    query.bindValue(":mdl", car->model);
    query.bindValue(":yofp", car->yearOfProduction);
    query.bindValue(":clr", car->color);
    query.bindValue(":nbm", car->number);
    query.bindValue(":pts", car->pts);
    query.bindValue(":act", car->active);
    query.bindValue(":cid", car->cid);
    if (!query.exec())
    {
        qDebug() << "Database::updateCar error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MyDB::addRent(Rent *rent)
{
    QSqlQuery query;
    query.prepare("INSERT INTO rent (bid, cid, fio, startts, endts, finished) VALUES (:bid, :cid, :fio, :startts, :endts, :finished)");
    query.bindValue(":bid", rent->bid);
    query.bindValue(":cid", rent->cid);
    query.bindValue(":fio", rent->fio);
    query.bindValue(":startts", rent->startts);
    query.bindValue(":endts", rent->endts);
    query.bindValue(":finished", rent->finished);
    if (!query.exec())
    {
        qDebug() << "Database::addRent error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MyDB::updateRent(Rent *rent)
{
    QSqlQuery query;
    query.prepare("UPDATE rent SET bid=:bid, cid=:cid, fio=:fio, startts=:startts, endts=:endts, finished=:finished WHERE rid=:rid");
    query.bindValue(":bid", rent->bid);
    query.bindValue(":cid", rent->cid);
    query.bindValue(":fio", rent->fio);
    query.bindValue(":startts", rent->startts);
    query.bindValue(":endts", rent->endts);
    query.bindValue(":finished", rent->finished);
    query.bindValue(":rid", rent->rid);
    if (!query.exec())
    {
        qDebug() << "Database::updateRent error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MyDB::addCarpark(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO carparks (name) VALUES (:name)");
    query.bindValue(":name", name);
    if (!query.exec())
    {
        qDebug() << "Database::addCarpark error: " << query.lastError().text();
        return false;
    }
    return true;
}

CarPark *MyDB::getCarPark(int pid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM carparks WHERE pid=" + QString().number(pid));
    query.bindValue(":bid", pid);
    if (!query.exec() || !query.next())
    {
        qDebug() << "Database::getCarPark query: " << query.lastQuery() << " query: " << query.lastError().text();
        return nullptr;
    }
    return new CarPark(query.value(0).toInt(),
                       query.value(1).toString());
}

Car *MyDB::getCar(int cid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM cars WHERE cid=" + QString().number(cid));
    query.bindValue(":cid", cid);
    if (!query.exec() || !query.next())
    {
        qDebug() << "Database::getCar query: " << query.lastQuery() << " query: " << query.lastError().text();
        return nullptr;
    }
    return new Car(query.value(0).toInt(),
                   query.value(1).toInt(),
                   query.value(2).toString(),
                   query.value(3).toString(),
                   query.value(4).toInt(),
                   query.value(5).toString(),
                   query.value(6).toString(),
                   query.value(7).toString(),
                   query.value(8).toBool());
}


int MyDB::getParkIdByCar(int cid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM cars WHERE cid=" + QString::number(cid));
    query.bindValue(":cid", cid);
    qDebug() << "MyDB::getParkIdByCar query: " << query.lastQuery() << " query: " << query.lastError().text();
    if (!query.exec() && query.next())
    {
        qDebug() << "MyDB::getParkIdByCar query: " << query.lastQuery() << " query: " << query.lastError().text();
        return -1;
    }
    return query.value("pid").toInt();
}

Rent *MyDB::getRent(int rid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM rent WHERE rid=" + QString().number(rid));
    query.bindValue(":rid", rid);
    if (!query.exec() || !query.next())
    {
        qDebug() << "Database::getRent query: " << query.lastQuery() << " query: " << query.lastError().text();
        return nullptr;
    }
    return new Rent(query.value(0).toInt(),
                    query.value(1).toInt(),
                    query.value(2).toInt(),
                    query.value(3).toString(),
                    query.value(4).toUInt(),
                    query.value(5).toUInt(),
                    query.value(8).toBool());
}

QList<CarPark> *MyDB::getCarParks()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM carparks");
    if (!query.exec())
    {
        qDebug() << "MyDB::getCarParks query: " << query.lastQuery() << " query: " << query.lastError().text();
    }
    QList<CarPark> *list = new QList<CarPark>();
    while (query.next())
    {
        CarPark *carpark = new CarPark();
        carpark->pid = query.value(0).toInt();
        carpark->name = query.value(1).toString();
        list->append(*carpark);
    }
    return list;
}

QList<Car> *MyDB::getCar()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM cars");
    if (!query.exec())
    {
        qDebug() << "MyDB::getCar query: " << query.lastQuery() << " query: " << query.lastError().text();
    }
    QList<Car> *list = new QList<Car>();
    while (query.next())
    {
        Car *car = new Car(query.value(0).toInt(),
                           query.value(1).toInt(),
                           query.value(2).toString(),
                           query.value(3).toString(),
                           query.value(4).toInt(),
                           query.value(5).toString(),
                           query.value(6).toString(),
                           query.value(7).toString(),
                           query.value(8).toBool());
        list->append(*car);
    }
    return list;
}
