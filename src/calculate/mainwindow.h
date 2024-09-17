#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smartcalc.h"
#include "creditcalc.h"
#include "depositcalc.h"
#include "qcustomplot.h"

class smartCalc;
class creditCalc;
class depositCalc;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_smart_calc.h"

#ifdef __cplusplus
}
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    smartCalc *  _smartcalc;
    creditCalc * _creditcalc;
    depositCalc * _depositcalc;
};
#endif // MAINWINDOW_H
