#include "plot.h"
//#include "smartcalc.h"
#include "ui_plot.h"
#include <QVector>

plot::plot(QWidget *parent, QLineEdit *src) :
    QDialog(parent),
    ui(new Ui::plot),
    m_src(src)

{

    ui->setupUi(this);
    ui->doubleSpinBox_x_max->setRange(-1000000, 1000000);
    ui->doubleSpinBox_y_max->setRange(-1000000, 1000000);
    ui->doubleSpinBox_y_min->setRange(-1000000, 1000000);
    ui->doubleSpinBox_x_min->setRange(-1000000, 1000000);
    ui->doubleSpinBox_x_max->setValue(10.0);
    ui->doubleSpinBox_y_max->setValue(10.0);
    ui->doubleSpinBox_x_min->setValue(-10.0);
    ui->doubleSpinBox_y_min->setValue(-10.0);

    QObject::connect(ui->pushButton_graph, &QPushButton::clicked, this, [=](){
        print_graph(m_src);
    });


}

plot::~plot()
{
    delete ui;
}

void plot::print_graph(QLineEdit *src){
    double x_min = ui->doubleSpinBox_x_min->value();
    double x_max = ui->doubleSpinBox_x_max->value();
    double y_min = ui->doubleSpinBox_y_min->value();
    double y_max = ui->doubleSpinBox_y_max->value();


    int num_points = 10000; // Желаемое количество точек
    double h = (x_max - x_min) / (num_points - 1); //шаг
    QVector<double> x, y;

    QString result_text = src->text();

    for (double X = x_min; X <= x_max; X += h) {
          x.push_back(X);

          long double result = 0;
          QString result_text = src->text();
          std::string result_text_std = result_text.toStdString();
          char result_text_char[result_text.length() + 1];
          std::copy(result_text_std.begin(), result_text_std.end(), result_text_char);
          result_text_char[result_text_std.size()] = '\0';
          s21_smart_calc(result_text_char, &result, X);

          y.push_back(result);
        }

       // добавляем один график в widget
       ui->graph_frame->addGraph();

       // говорим, что отрисовать нужно график по нашим двум массивам x и y
       ui->graph_frame->graph(0)->setData(x, y);

       QCPScatterStyle scatterStyle;
               scatterStyle.setShape(QCPScatterStyle::ssCircle); // Установка формы точек (круг)
               scatterStyle.setSize(2);
        ui->graph_frame->graph(0)->setScatterStyle(scatterStyle);

       // устанавливаем область, которая будет показываться на графике
       ui->graph_frame->xAxis->setRange(x_min, x_max);
       ui->graph_frame->yAxis->setRange(y_min, y_max);

       // задаем возможность зумировать график
       ui->graph_frame->setInteraction(QCP::iRangeZoom, true);

       // задаем цвет точки и толщину линии
       ui->graph_frame->graph(0)->setPen(QColor(61, 82, 62, 255));
       QPen graphPen = ui->graph_frame->graph(0)->pen();
       graphPen.setWidth(2);
       ui->graph_frame->graph(0)->setPen(graphPen);

       // перерисуем график на нашем graph_frame
       ui->graph_frame->replot();

       ui->graph_frame->graph(0)->setLineStyle(QCPGraph::lsNone); // Убрать линии

}


