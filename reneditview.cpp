#include "reneditview.h"
#include "ui_reneditview.h"
#include <QDebug>

RenEditView::RenEditView(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::RenEditView)
{
    ui->setupUi(this);
    connect(ui->pushButtonRent, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
    rent = new Rent();
    parkModel = new QSqlTableModel(this);
    carModel = new QSqlTableModel(this);
    updateParkModel();
    updateCarModel();
    QDate currentDate = QDate::currentDate();
    QDateTime currentDateTime(currentDate, QTime(12, 0, 0));
    ui->dateTimeEditS->setDateTime(currentDateTime);
    ui->dateTimeEditE->setDateTime(currentDateTime);
}

RenEditView::~RenEditView()
{
    delete ui;
}

void RenEditView::setRent(Rent *rent)
{
    this->rent = rent;
    Car *car = db.getCar(rent->cid);
    qDebug() << "cid =" << rent->cid << ", pid =" << car->pid;
    for (int row = 0; row < parkModel->rowCount(); ++row)
    {
        if (parkModel->record().value("pid").toInt() == car->pid) {
            ui->comboBoxPark->setCurrentIndex(row);
            break;
        }
    }
    updateCarModel();
    for (int row = 0; row < carModel->rowCount(); ++row)
    {
        if (carModel->record().value("cid").toInt() == rent->cid) {
            ui->comboBoxNumber->setCurrentIndex(row);
            break;
        }
    }
    ui->lineEditFIO->setText(rent->fio);
    ui->dateTimeEditS->setDateTime(QDateTime::fromSecsSinceEpoch(rent->startts));
    ui->dateTimeEditE->setDateTime(QDateTime::fromSecsSinceEpoch(rent->endts));
}

Rent *RenEditView::getRent()
{
    return rent;
}

void RenEditView::updateParkModel()
{
    parkModel->setTable("carparks");
    parkModel->select();
    ui->comboBoxPark->setModel(parkModel);
    currentPark = ui->comboBoxPark->currentText().toInt();
    ui->comboBoxPark->setModelColumn(parkModel->fieldIndex("name"));
}

void RenEditView::updateCarModel()
{
    carModel->setTable("cars");
    carModel->setFilter("active=1 AND pid=" + QString::number(currentPark));
    carModel->select();
    ui->comboBoxNumber->setModel(carModel);
    currentCar = ui->comboBoxNumber->currentText().toInt();
    ui->comboBoxNumber->setModelColumn(carModel->fieldIndex("number"));
}

void RenEditView::on_comboBoxPark_currentTextChanged(const QString &arg1)
{
    QList<CarPark> *list = db.getCarParks();
    QListIterator<CarPark> i(*list);
    while (i.hasNext())
    {
        CarPark park = i.next();
        if (QString::compare(arg1, park.name, Qt::CaseInsensitive) == 0)
        {
            currentPark = park.pid;
            updateCarModel();
            return;
        }
    }
}

void RenEditView::on_comboBoxNumber_currentTextChanged(const QString &arg1)
{
    QList<Car> *list = db.getCar();
    QListIterator<Car> i(*list);
    while (i.hasNext())
    {
        Car car = i.next();
        if (QString::compare(arg1, car.number, Qt::CaseInsensitive) == 0)
        {
            currentCar = car.cid;
            rent->cid = car.cid;
            return;
        }
    }
}

void RenEditView::on_lineEditFIO_textChanged(const QString &arg1){ rent->fio = arg1; }
void RenEditView::on_dateTimeEditS_dateTimeChanged(const QDateTime &dateTime) { rent->startts = dateTime.toSecsSinceEpoch(); }
void RenEditView::on_dateTimeEditE_dateTimeChanged(const QDateTime &dateTime) { rent->endts = dateTime.toSecsSinceEpoch(); }
void RenEditView::on_pushButtonRent_clicked(){}
void RenEditView::on_pushButtonCancel_clicked() {}
