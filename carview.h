#ifndef CARVIEW_H
#define CARVIEW_H

#include "mydb.h"
#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QInputDialog>

namespace Ui {
class CarView;
}

class CarView : public QWidget
{
    Q_OBJECT

public:
    explicit CarView(QWidget *parent = nullptr);
    ~CarView();
    void search(QString query);

private slots:
    void on_pushButtonSave_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonAdd_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonDisableCar_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::CarView *ui;
    MyDB db = MyDB::instanse;
    QSqlTableModel *model;
    QSqlTableModel *carPacksModel;
    int currentPark;
    Car *currentCar;
    QString carFilter;
    void updateParksModel();
    void updateModel();
    void carcardClear();
};

#endif // CARVIEW_H
