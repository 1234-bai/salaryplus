#ifndef CHANGEORDELETE_H
#define CHANGEORDELETE_H

#include <QDialog>
#include <people.h>

namespace Ui {
class changeORdelete;
}

class changeORdelete : public QDialog
{
    Q_OBJECT

public:
    explicit changeORdelete(people pe,QWidget *parent = nullptr);
    ~changeORdelete();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    people pe;
    Ui::changeORdelete *ui;
};

#endif // CHANGEORDELETE_H
