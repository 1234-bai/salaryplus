#ifndef CHANGE_CODE_H
#define CHANGE_CODE_H

#include <QDialog>

namespace Ui {
class change_code;
}

class change_code : public QDialog
{
    Q_OBJECT

public:
    explicit change_code(QWidget *parent = nullptr);
    ~change_code();

private slots:
    void on_pushButton_clicked();

private:
    Ui::change_code *ui;
};

#endif // CHANGE_CODE_H
