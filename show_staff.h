#ifndef SHOW_STAFF_H
#define SHOW_STAFF_H

#include <QDialog>

namespace Ui {
class show_staff;
}

class show_staff : public QDialog
{
    Q_OBJECT

public:
    explicit show_staff(QWidget *parent = nullptr);
    ~show_staff();

private slots:
    void on_pushButton_clicked();

private:
    Ui::show_staff *ui;

};

#endif // SHOW_STAFF_H
