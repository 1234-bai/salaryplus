#ifndef ADDMIN_H
#define ADDMIN_H

#include <QDialog>

namespace Ui {
class addmin;
}

class addmin : public QDialog
{
    Q_OBJECT

public:
    explicit addmin(QWidget *parent = nullptr);
    ~addmin();

private slots:
    void on_search_clicked();

    void on_add_clicked();

    void on_change_clicked();

    void on_deletee_clicked();

    void on_count_clicked();

    void on_back_clicked();

    void on_recover_clicked();

private:
    Ui::addmin *ui;
};

#endif // ADDMIN_H
