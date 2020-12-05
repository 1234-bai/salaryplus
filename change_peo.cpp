#include "change_peo.h"
#include "ui_change_peo.h"
#include "List.h"
#include "Note.h"
#include "people.h"
#include "date.h"
#include <QMessageBox>
#include <QRegExpValidator>

change_peo::change_peo(int id,QString strr,QWidget *parent) :
    QDialog(parent),IDD(id),strr(strr),
    ui(new Ui::change_peo)
{
    ui->setupUi(this);
    ui->lineEdit_3->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_4->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_5->setValidator(new QIntValidator(1,100000000,this));
    QRegExp rx("^(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx,this));
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char *filename=str.c_str();
    ui->display_id->setText(QString::number(IDD));
    List<people>li1(filename);
    Note<people> *p=searchidInList(li1,id);
    if(p==0){
        QMessageBox::warning(this,tr("注意"),tr("本月无此人数据"));
        this->close();
    }
    else{
        people pe=p->data;
        ui->lineEdit->setText(QString::fromStdString(pe.getName()));
        ui->lineEdit_2->setText(QString::fromStdString(pe.getPhone()));
        ui->lineEdit_3->setText(QString::number(pe.getBasic_salary()));
        ui->lineEdit_4->setText(QString::number(pe.getPerf_salary()));
        ui->lineEdit_5->setText(QString::number(pe.getBonus()));
        this->show();
    }
}

change_peo::~change_peo()
{
    delete ui;
}

void change_peo::on_pushButton_clicked()
{
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char* filename=str.c_str();
    List<people>li(filename);
    Note<people> *p=searchidInList(li,IDD);
    if(p==0){
        QMessageBox::warning(this,tr("注意"),tr("本月无此人数据"));
        this->close();
    }
    if(strr==tr("修改")){
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
    }
    else if(strr==tr("删除")){
        li.deleteNode(p);
    }
    else{
        QMessageBox::warning(this,tr("坏了"),tr("出事了"));
    }
    List<Date>li0fda("date.txt");
    Note<Date>*d=searchDate(li0fda,da);
    d->data.changeSalary(getsTotallSalary(li));
    li.List_to_file(filename);
    li0fda.List_to_file("date.txt");
    QMessageBox::information(this,tr("注意"),strr.append("成功"));
    this->close();
}
