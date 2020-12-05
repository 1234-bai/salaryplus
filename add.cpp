#include "add.h"
#include "ui_add.h"
#include "date.h"
#include "Note.h"
#include <QMessageBox>
#include <QInputDialog>
#include "change_peo.h"
#include "id.h"
#include <QValidator>
#include <QRegExpValidator>

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    ui->lineEdit_6->setFocus();
    ui->lineEdit_6->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_3->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_4->setValidator(new QIntValidator(1,100000000,this));
    ui->lineEdit_5->setValidator(new QIntValidator(1,100000000,this));
    QRegExp rx("^(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$");
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx,this));
    Date da;
    da.getNowdate();
    std::string str=da.toDateString();
    const char * filename=str.c_str();
    li.file_to_List(filename);
}

Add::~Add()
{
    delete ui;
}

void Add::on_pushButton_2_clicked()
{
    ui->pushButton->click();
    if(!li.is_empty()) {
        Date da;
        da.getNowdate();
        std::string str=da.toDateString();
        const char * filename=str.c_str();
        li.List_to_file(filename);
        da.changeSalary(getsTotallSalary(li));
        List<Date>la("date.txt");
        Note<Date> *p=searchDate(la,da);
        if(p==0){
            la.insertNote(new Note<Date>(da));
        }
        else p->data.changeSalary(getsTotallSalary(li));
        la.List_to_file("date.txt");
    }
    close();
}

void Add::on_pushButton_clicked()
{
    Date da;
    da.getNowdate();
    int id=ui->lineEdit_6->text().toInt();
    std::string name=ui->lineEdit->text().toStdString();
    std::string phone=ui->lineEdit_2->text().toStdString();
    long long bsalary=ui->lineEdit_3->text().toLongLong();
    long long psalary=ui->lineEdit_4->text().toLongLong();
    long long bon=ui->lineEdit_5->text().toLongLong();
    if(id || bsalary || psalary || bon){
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_6->setFocus();
        people pe(id,name,phone,bsalary,psalary,bon,da.getyear(),da.getmonth());
        if(li.insertNote(new Note<people>(pe))) {
            QMessageBox::information(this,tr("哈哈"),tr("录入成功"));
            List<ID>li0fid("id0fstaff.txt");
            ID idd(id,QString::number(id).toStdString());
            li0fid.insertNote(new Note<ID>(idd));
            li0fid.List_to_file("id0fstaff.txt");
        }
        else QMessageBox::warning(this,tr("很遗憾"),tr("录入失败了喵，人员重复了喵"));
    }
}
