#include "smartcalc.h"
#include "ui_smartcalc.h"
#include "mainwindow.h"
#include "../s21_smart_calc.h"
#include <cstring>

smartCalc::smartCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smartCalc)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));

    QObject::connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));

    QObject::connect(ui->pushButton_closeBracket, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_openBracket, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));

    QObject::connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));

    QObject::connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));
    QObject::connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(calc_button_pressed()));

    QObject::connect(ui->pushButton_equality, SIGNAL(clicked()), this, SLOT(show_result()));

}

smartCalc::~smartCalc()
{
    delete ui;
}


void smartCalc::on_popButton_clicked()
{
    hide();
    window = new MainWindow();
    window->show();
    this->deleteLater();
}

void smartCalc::calc_button_pressed(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        ui->lineEdit->insert(button->text());
        ui->lineEdit->update();
        }
}

void smartCalc::show_result(){

    QString result_text = ui->lineEdit->text();
    std::string result_text_std = result_text.toStdString();
    char result_text_char[result_text.length() + 1];
    std::copy(result_text_std.begin(), result_text_std.end(), result_text_char);
    result_text_char[result_text_std.size()] = '\0';

    QString x_text = ui->lineEdit_x->text();
    bool ok = 1;
    double x = 0.0;
    if (result_text_std.find('x') != std::string::npos){
        x = x_text.toDouble(&ok);
    }

    if (ok){
        long double result = 0.0;
        int status = s21_smart_calc(result_text_char, &result, x);
        QString result_number = QString::number(static_cast<double>(result), 'g', 10);
        if (status == 0){
            ui->lineEdit->setText(result_number);
        } else {
            ui->lineEdit->setText("ERROR");
        }
    } else {
        ui->lineEdit->setText("ERROR");
    }

}

void smartCalc::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked){
        _plot = new plot(nullptr, ui->lineEdit);
        _plot->show();
    } else {
        if (_plot != nullptr)
                {
                    _plot->hide();
                    delete _plot;
                    _plot = nullptr;
                }
    }

}

void smartCalc::on_pushButton_ac_clicked()
{
    ui->lineEdit->setText("");
}

