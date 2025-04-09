#ifndef RENEDITVIEW_H
#define RENEDITVIEW_H

#include "mydb.h"
#include "rent.h"
#include "carpark.h"
#include "car.h"
#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class RenEditView;
}

class RenEditView : public QDialog
{
    Q_OBJECT

public:
    explicit RenEditView(QDialog *parent = nullptr);
    ~RenEditView();
    void setRent(Rent *rent);
    Rent *getRent();

private slots:
    void on_comboBoxPark_currentTextChanged(const QString &arg1);

    void on_comboBoxNumber_currentTextChanged(const QString &arg1);

    void on_lineEditFIO_textChanged(const QString &arg1);

    void on_dateTimeEditS_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEditE_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButtonRent_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RenEditView *ui;
    MyDB db = MyDB::instanse;
    Rent *rent;
    QSqlTableModel *parkModel;
    QSqlTableModel *carModel;
    void updateParkModel();
    void updateCarModel();
    int currentPark;
    int currentCar;
};

#endif // RENEDITVIEW_H
