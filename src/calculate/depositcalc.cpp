#include "depositcalc.h"
#include "ui_depositcalc.h"

depositCalc::depositCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::depositCalc)
{
    ui->setupUi(this);
    ui->capitaization->setRange(0,1);
    ui->deposit->setRange(0,99999999999999);
    ui->interest->setRange(0,100);
    ui->payfrc->setRange(0, 99999999999);
    ui->replenishment->setRange(0,99999999999999);
    ui->tax->setRange(0,100);
    ui->term->setRange(0, 99999999);
    ui->withdraw->setRange(0, 9999999999);
}

depositCalc::~depositCalc()
{
    delete ui;
}

void depositCalc::on_PopButton_clicked()
{
    hide();
    window = new MainWindow();
    window->show();
    this->deleteLater();
}


void depositCalc::on_pushButton_calculate_clicked()
{
    double initial_deposit = ui->deposit->value();
    int period_in_months = ui->term->value();
    double initial_interest = ui->interest->value();
    int payment_periodicity = ui->payfrc->value();
    int is_capitalized = ui->capitaization->value();
    double replenishment_amount = ui->replenishment->value();
    double withdraw_amount = ui->withdraw->value();
    double tax_interest = ui->tax->value();
    double accured_interest = 0,  tax_amount = 0, deposit_amount = 0;
    int status = s21_deposit_calc(initial_deposit, period_in_months, initial_interest,
                     payment_periodicity, is_capitalized, replenishment_amount,
                     withdraw_amount, tax_interest, &accured_interest,
                     &tax_amount, &deposit_amount);
    if (status == 0){
        QString res_interest = QString::number((accured_interest) , 'g', 7);
        QString tax_pay = QString::number((tax_amount) , 'g', 7);
        QString dep_res = QString::number((deposit_amount) , 'g', 7);

        ui->accuredInterest->setText(res_interest);
        ui->taxAmount->setText(tax_pay);
        ui->depositRes->setText(dep_res);
    } else {
        ui->taxAmount->setText("ERROR");
        ui->accuredInterest->setText("");
        ui->depositRes->setText("");
    }

}

