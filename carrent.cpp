#include "carrent.h"
#include "ui_carrent.h"

CarRent::CarRent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarRent)
{
    ui->setupUi(this);

    tab1 = new CarView();
    tab2 = new RentView();
    ui->tabWidget->addTab(tab1, "Автобаза");
    ui->tabWidget->addTab(tab2, "Аренда машин");
}

CarRent::~CarRent()
{
    delete ui;
}

void CarRent::on_pushButtonSearch_clicked()
{
    ui->tabWidget->setCurrentWidget(tab1);
    tab1->search(ui->lineEditSearch->text());
}

void CarRent::on_pushButtonRent_clicked()
{
    ui->tabWidget->setCurrentWidget(tab2);
    tab2->addRent();
}
