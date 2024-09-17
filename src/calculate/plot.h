#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include <QLineEdit>
#include <QVector>


namespace Ui {
class plot;
}

#ifdef __cplusplus
extern "C" {
#endif

#include "../s21_smart_calc.h"

#ifdef __cplusplus
}
#endif

class plot : public QDialog
{
    Q_OBJECT

public:
    explicit plot(QWidget *parent = nullptr, QLineEdit * src = nullptr);
    ~plot();

private slots:
    void print_graph(QLineEdit * src);

private:
    Ui::plot *ui;
    QLineEdit *m_src;
};

#endif // PLOT_H
