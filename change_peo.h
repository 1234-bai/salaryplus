#ifndef CHANGE_PEO_H
#define CHANGE_PEO_H

#include <QDialog>

namespace Ui {
class change_peo;
}

class change_peo : public QDialog
{
    Q_OBJECT

public:
    explicit change_peo(int id=0,QString str="hahahaha",QWidget *parent = nullptr);
    ~change_peo();
    int IDD;
    QString strr;

private slots:
    void on_pushButton_clicked();

private:
    Ui::change_peo *ui;

};

#endif // CHANGE_PEO_H
