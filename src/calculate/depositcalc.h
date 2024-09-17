#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class depositCalc;
}

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_smart_calc.h"

#ifdef __cplusplus
}
#endif


class depositCalc : public QDialog
{
    Q_OBJECT

public:
    explicit depositCalc(QWidget *parent = nullptr);
    ~depositCalc();

private slots:
    void on_PopButton_clicked();
    void on_pushButton_calculate_clicked();

private:
    Ui::depositCalc *ui;
    QMainWindow * window;
};

#endif // DEPOSITCALC_H
