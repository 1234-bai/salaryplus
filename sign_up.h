#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Sign_up; }
QT_END_NAMESPACE

class Sign_up : public QDialog
{
    Q_OBJECT

public:
    Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::Sign_up *ui;

};
#endif // SIGN_UP_H
