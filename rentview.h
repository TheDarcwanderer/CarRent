#ifndef RENTVIEW_H
#define RENTVIEW_H

#include "mydb.h"
#include "reneditview.h"
#include <QWidget>
#include <QDateTime>
#include <QSqlTableModel>

namespace Ui {
class RentView;
}

class RentView : public QWidget
{
    Q_OBJECT

public:
    explicit RentView(QWidget *parent = nullptr);
    ~RentView();
    void addRent();

private slots:
    void on_pushButtonRent_clicked();

    void on_pushButtonRentEdit_clicked();

    void on_pushButtonRentEnd_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::RentView *ui;
    MyDB db = MyDB::instanse;
    QSqlTableModel *model;
    Rent *currentRent;
    void updateModel();
};

#endif // RENTVIEW_H
