#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../s21_smart_calc.h"
#include "smartcalc.h"
#include "creditcalc.h"
#include "depositcalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    hide();
    _smartcalc = new smartCalc(this);
    _smartcalc->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    _creditcalc = new creditCalc(this);
    _creditcalc->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    hide();
    _depositcalc = new depositCalc(this);
    _depositcalc->show();
}

