#include "carview.h"
#include "ui_carview.h"
#include <QDebug>

CarView::CarView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QTableView::SelectionBehavior(1));
    model = new QSqlTableModel(this);
    carPacksModel = new QSqlTableModel(this);
    updateParksModel();
    updateModel();
}

CarView::~CarView()
{
    delete ui;
}

void CarView::search(QString query)
{
    carFilter = query;
    updateModel();
}

void CarView::updateParksModel()
{
    carPacksModel->setTable("carparks");
    carPacksModel->select();
    ui->comboBox->setModel(carPacksModel);
    currentPark = ui->comboBox->currentText().toInt();
    ui->comboBox->setModelColumn(carPacksModel->fieldIndex("name"));
}

void CarView::updateModel()
{
    model->setTable("cars");
    if (carFilter.isEmpty())
    {
        model->setFilter("active=1 AND pid=" + QString::number(currentPark));
    }
    else
    {
        model->setFilter("active=1 AND pid=" + QString::number(currentPark) + " AND number='" + carFilter + "'");
    }
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    //ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    //ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    model->setHeaderData(3, Qt::Horizontal, "Модель");
    model->setHeaderData(6, Qt::Horizontal, "Номер");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CarView::carcardClear()
{
    ui->lineEditFabricator->setText("");
    ui->lineEditModel->setText("");
    ui->lineEditYear->setText("");
    ui->lineEditColor->setText("");
    ui->lineEditNumber->setText("");
    ui->lineEditPTS->setText("");
    currentCar = nullptr;
}

void CarView::on_pushButtonSave_clicked()
{
    bool n = false;
    if (currentCar == nullptr)
    {
        currentCar = new Car();
        n = true;
    }
    currentCar->pid = currentPark;
    currentCar->fabricator = ui->lineEditFabricator->text();
    currentCar->model = ui->lineEditModel->text();
    currentCar->yearOfProduction = ui->lineEditYear->text().toInt();
    currentCar->color = ui->lineEditColor->text();
    currentCar->number = ui->lineEditNumber->text();
    currentCar->pts = ui->lineEditPTS->text();
    currentCar->active = true;
    if (n)
    { db.addCar(currentCar); }
    else
    { db.updateCar(currentCar); }
    updateModel();
}

void CarView::on_tableView_clicked(const QModelIndex &index)
{
    index.data();
    for (const QModelIndex &index : ui->tableView->selectionModel()->selectedIndexes())
    {
        QVariant v = index.data();
        switch (index.column())
        {
        case 0: currentCar = db.getCar(v.toInt()); break;
        case 1: break;
        case 2: ui->lineEditFabricator->setText(v.toString()); break;
        case 3: ui->lineEditModel->setText(v.toString()); break;
        case 4: ui->lineEditYear->setText(v.toString()); break;
        case 5: ui->lineEditColor->setText(v.toString()); break;
        case 6: ui->lineEditNumber->setText(v.toString()); break;
        case 7: ui->lineEditPTS->setText(v.toString()); break;
        case 8: break;
        }
    }
}

void CarView::on_pushButtonAdd_clicked() { carcardClear(); }

void CarView::on_pushButtonSearch_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(nullptr,
                                         "Поиск",
                                         "Введите значение:",
                                         QLineEdit::Normal,
                                         "",
                                         &ok);
    if (ok && !text.isEmpty()) { search(text); }
}

void CarView::on_pushButtonDisableCar_clicked()
{
    currentCar->active = false;
    db.updateCar(currentCar);
    carcardClear();
    updateModel();
}

void CarView::on_comboBox_currentTextChanged(const QString &arg1)
{
    QList<CarPark> *list = db.getCarParks();
    QListIterator<CarPark> i(*list);
    while (i.hasNext())
    {
        CarPark park = i.next();
        if (QString::compare(arg1, park.name, Qt::CaseInsensitive) == 0)
        {
            currentPark = park.pid;
            updateModel();
            carcardClear();
            return;
        }
    }
}
