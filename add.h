#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include "List.h"
#include "people.h"

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Add *ui;
    List<people>li;
};

#endif // ADD_H
