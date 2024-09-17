#ifndef SMARTCALC_H
#define SMARTCALC_H

#include "plot.h"
#include "qcustomplot.h"
// #include "mainwindow.h"
#include <QDialog>
#include <QWidget>


namespace Ui {
class smartCalc;
}

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_smart_calc.h"

#ifdef __cplusplus
}
#endif

class smartCalc : public QDialog
{
    Q_OBJECT

public:
    explicit smartCalc(QWidget *parent = nullptr);
    ~smartCalc();


private slots:
    void on_popButton_clicked();
    void calc_button_pressed();
    void show_result();
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_ac_clicked();

private:
    Ui::smartCalc *ui;
    QMainWindow * window;
    plot * _plot;
};

#endif // SMARTCALC_H
