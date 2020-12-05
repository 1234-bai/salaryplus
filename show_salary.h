#ifndef SHOW_SALARY_H
#define SHOW_SALARY_H

#include <QDialog>

namespace Ui {
class show_salary;
}

class show_salary : public QDialog
{
    Q_OBJECT

public:
    explicit show_salary(int year=2020,int month=6,QWidget *parent = nullptr);
    ~show_salary();

private slots:
    void on_pushButton_clicked();

private:
    int year;
    int month;
    Ui::show_salary *ui;
};

#endif // SHOW_SALARY_H
