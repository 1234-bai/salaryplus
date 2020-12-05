#ifndef COUNT_H
#define COUNT_H

#include <QDialog>

namespace Ui {
class count;
}

class count : public QDialog
{
    Q_OBJECT

public:
    explicit count(QWidget *parent = nullptr);
    ~count();

private slots:
    void on_pushButton_clicked();

private:
    Ui::count *ui;
};

#endif // COUNT_H
