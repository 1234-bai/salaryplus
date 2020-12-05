#include "changeordelete.h"
#include "ui_changeordelete.h"
#include "date.h"
#include <QMessageBox>
#include <QRegExpValidator>

changeORdelete::changeORdelete(people pe,QWidget *parent) :
    QDialog(parent),pe(pe),
    ui(new Ui::changeORdelete)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("录入更新"));
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char *filename=str.c_str();
    List<people>li(filename);
    li.List_to_file(filename);
    ui->display_id->setText(QString::number(pe.getid()));
    ui->lineEdit->setText(QString::fromStdString(pe.getName()));
    ui->lineEdit_2->setText(QString::fromStdString(pe.getPhone()));
    ui->lineEdit_3->setText(QString::number(pe.getBasic_salary()));
    ui->lineEdit_4->setText(QString::number(pe.getPerf_salary()));
    ui->lineEdit_5->setText(QString::number(pe.getBonus()));
    ui->lineEdit_3->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_4->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_5->setValidator(new QIntValidator(1,100000000,this));
    QRegExp rx("^(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx,this));
}

changeORdelete::~changeORdelete()
{
    delete ui;
}

void changeORdelete::on_pushButton_clicked()
{
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char *filename=str.c_str();
    List<people>li(filename);
    Note<people>*p=searchidInList(li,pe.getid());
    li.deleteNode(p);
    QMessageBox::information(this,tr("注意"),tr("删除成功"));
    li.List_to_file(filename);
    accept();
}

void changeORdelete::on_pushButton_2_clicked()
{
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char *filename=str.c_str();
    List<people>li(filename);
    Note<people>*p=searchidInList(li,pe.getid());
    std::string name=ui->lineEdit->text().toStdString();
    std::string phone=ui->lineEdit_2->text().toStdString();
    long long bsalary=ui->lineEdit_3->text().toLongLong();
    long long psalary=ui->lineEdit_4->text().toLongLong();
    long long bon=ui->lineEdit_5->text().toLongLong();
    p->data.changeName(name);
    p->data.changeBonus(bon);
    p->data.changePhone(phone);
    p->data.changePerf_salary(psalary);
    p->data.changeBasic_salary(bsalary);
    QMessageBox::information(this,tr("注意"),tr("录入成功"));
    li.List_to_file(filename);
    accept();
}
