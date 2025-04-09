#include "rentview.h"
#include "ui_rentview.h"
#include <QDebug>

RentView::RentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RentView)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    ui->tableView->setSelectionBehavior(QTableView::SelectionBehavior(1));
    updateModel();

    QDate currentDate = QDate::currentDate();

    QDate monday = currentDate.addDays(-currentDate.dayOfWeek() + 1);
    QDateTime mondayStart(monday, QTime(0, 0, 0));
    QDate sunday = currentDate.addDays(7 - currentDate.dayOfWeek());
    QDateTime sundayEnd(sunday, QTime(23, 59, 59));

    ui->dateEditS->setDateTime(mondayStart);
    ui->dateEditE->setDateTime(sundayEnd);
}

RentView::~RentView()
{
    delete ui;
}

void RentView::addRent()
{
    RenEditView dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        db.addRent(dialog.getRent());
        updateModel();
    }
}

void RentView::updateModel()
{
    model->setTable("rent");
    //model->setFilter("finished=1");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    //ui->tableView->hideColumn(3);
    //ui->tableView->hideColumn(4);
    //ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    model->setHeaderData(3, Qt::Horizontal, "ФИО");
    model->setHeaderData(4, Qt::Horizontal, "C числа");
    model->setHeaderData(5, Qt::Horizontal, "По число");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void RentView::on_pushButtonRent_clicked()
{
    RenEditView dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        db.addRent(dialog.getRent());
        updateModel();
    }
}

void RentView::on_pushButtonRentEdit_clicked()
{
    RenEditView dialog;
    if (currentRent != nullptr)
    { dialog.setRent(currentRent); }
    else
    { return; }
    if (dialog.exec() == QDialog::Accepted)
    {
        db.updateRent(dialog.getRent());
        updateModel();
    }
}

void RentView::on_pushButtonRentEnd_clicked()
{

}

void RentView::on_tableView_clicked(const QModelIndex &index)
{
    index.data();
    for (const QModelIndex &index : ui->tableView->selectionModel()->selectedIndexes())
    {
        QVariant v = index.data();
        if (index.column() == 0)
        {
            currentRent = db.getRent(v.toInt());
            return;
        }
    }
}
