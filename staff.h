#ifndef STAFF_H
#define STAFF_H

#include <QDialog>

namespace Ui {
class staff;
}

class staff : public QDialog
{
    Q_OBJECT

public:
    explicit staff(int id=0,QWidget *parent = nullptr);
    ~staff();

private slots:
    void on_pushButton_clicked();

private:
    int IDD;
    Ui::staff *ui;
};

#endif // STAFF_H
