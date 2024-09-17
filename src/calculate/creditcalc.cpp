#include "creditcalc.h"
#include "ui_creditcalc.h"
#include "smartcalc.h"
#include "mainwindow.h"
#include "../s21_smart_calc.h"

creditCalc::creditCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditCalc)
{
    ui->setupUi(this);
    ui->doubleSpinBox_interestRate->setRange(0, 9999999999999);
    ui->doubleSpinBox_totalLoanAmount->setRange(0, 9999999999999);
    ui->doubleSpinBox_term->setRange(0, 9999999999999);
}

creditCalc::~creditCalc()
{
    delete ui;
}

void creditCalc::on_PopButton_clicked()
{
    hide();
    window = new MainWindow();
    window->show();
    this->deleteLater();
}


void creditCalc::on_pushButton_calculate_clicked()
{
    long double credit_amount = ui->doubleSpinBox_totalLoanAmount->value();
    long double month = ui->doubleSpinBox_term->value();
    long double interest = ui->doubleSpinBox_interestRate->value();
    long double total_payment= 0,overpay = 0;
    if (ui->radioButton_annuity->isChecked()){
       long double pay_for_month = 0;
        s21_annuity_calculation(credit_amount, month, interest, &pay_for_month, &total_payment, &overpay);

        ui->label_monthlyPayment_res->setText(QString::number(static_cast<double>(pay_for_month) , 'g', 7));

    } else if (ui->radioButton_differentiated->isChecked()){
        long double pay_for_month_min = 0, pay_for_month_max = 0;
        s21_diff_calculation(credit_amount, month, interest, &pay_for_month_min, &pay_for_month_max, &total_payment, &overpay);

        ui->label_monthlyPayment_res->setText(QString::number(pay_for_month_max, 'g', 7) + "..." + QString::number(pay_for_month_min, 'g', 7));
    }

    QString overpay_res = QString::number(static_cast<double>(overpay), 'g', 7);
    QString total_payment_res = QString::number(static_cast<double>(total_payment), 'g', 7);

    ui->label_loanOverpayment_res->setText(overpay_res);
    ui->label_totalPayment_res->setText(total_payment_res);
}

