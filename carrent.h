#ifndef CARRENT_H
#define CARRENT_H

#include "carview.h"
#include "rentview.h"
#include <QMainWindow>

namespace Ui {
class CarRent;
}

class CarRent : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarRent(QWidget *parent = nullptr);
    ~CarRent();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonRent_clicked();

private:
    Ui::CarRent *ui;
    CarView* tab1;
    RentView* tab2;
};

#endif // CARRENT_H
