#include "show_salary.h"
#include "ui_show_salary.h"
#include "date.h"
#include "people.h"
#include "List.h"
#include <QMessageBox>

show_salary::show_salary(int year,int month,QWidget *parent) :
    QDialog(parent),year(year),month(month),
    ui(new Ui::show_salary)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("人员工资一览"));
    Date da(year,month);
    std::string st=da.toDateString();
    const char *filename=st.c_str();
    List<people>li(filename);
    int length=li.length;
    ui->ta->setRowCount(length);
    ui->ta->setColumnCount(11);
    ui->ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header<<"编号"<<"姓名"<<"电话"<<"年份"<<"月份"<<"底薪"<<"绩效"<<"奖金"<<"应发工资"<<"扣税"<<"实发工资";
    ui->ta->setHorizontalHeaderLabels(header);
    li.reset();
    int i=0;
    for(i=0;i<li.length;++i){
        people pe=li.popNote();
        ui->ta->setItem(i,0,new QTableWidgetItem(QString::number(pe.getid())));
        ui->ta->setItem(i,1,new QTableWidgetItem(QString::fromStdString(pe.getName())));
        ui->ta->setItem(i,2,new QTableWidgetItem(QString::fromStdString(pe.getPhone())));
        ui->ta->setItem(i,3,new QTableWidgetItem(QString::number(pe.getYear())));
        ui->ta->setItem(i,4,new QTableWidgetItem(QString::number(pe.getMonth())));
        ui->ta->setItem(i,5,new QTableWidgetItem(QString::number(pe.getBasic_salary())));
        ui->ta->setItem(i,6,new QTableWidgetItem(QString::number(pe.getPerf_salary())));
        ui->ta->setItem(i,7,new QTableWidgetItem(QString::number(pe.getBonus())));
        ui->ta->setItem(i,8,new QTableWidgetItem(QString::number(pe.getTotal_salary())));
        ui->ta->setItem(i,9,new QTableWidgetItem(QString::number(pe.getTax())));
        ui->ta->setItem(i,10,new QTableWidgetItem(QString::number(pe.getFinal_salary())));
        li.moveNext();
    }
    ui->ta->show();
}

show_salary::~show_salary()
{
    delete ui;
}

void show_salary::on_pushButton_clicked()
{
    int rule=-1*(ui->listWidget->currentRow()+1);
    ui->ta->clear();
    Date da(year,month);
    std::string st=da.toDateString();
    const char *filename=st.c_str();
    List<people>li(filename);
    long long beginsa=ui->spinBox->value();
    long long endsa=ui->spinBox_2->value();
    List<people>li1;
    drawPartList(li,li1,beginsa,endsa,rule);
    switch (rule) {
    case -1:
        li1.sortList(basicrule);
        break;
    case -2:
        li1.sortList(perrule);
        break;
    case -3:
        li1.sortList(bonusrule);
        break;
    case -4:
        li1.sortList(totalrule);
        break;
    case -5:
        li1.sortList(taxrule);
        break;
    case -6:
        li1.sortList(finallrule);
    default:
        break;
    }
    int length=li1.length;
    ui->ta->setRowCount(length);
    ui->ta->setColumnCount(11);
    ui->ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header<<"编号"<<"姓名"<<"电话"<<"年份"<<"月份"<<"底薪"<<"绩效"<<"奖金"<<"应发工资"<<"扣税"<<"实发工资";
    ui->ta->setHorizontalHeaderLabels(header);
    li1.reset();
    int i=0;
    for(i=0;i<length;++i){
        people pe=li1.popNote();
        ui->ta->setItem(i,0,new QTableWidgetItem(QString::number(pe.getid())));
        ui->ta->setItem(i,1,new QTableWidgetItem(QString::fromStdString(pe.getName())));
        ui->ta->setItem(i,2,new QTableWidgetItem(QString::fromStdString(pe.getPhone())));
        ui->ta->setItem(i,3,new QTableWidgetItem(QString::number(pe.getYear())));
        ui->ta->setItem(i,4,new QTableWidgetItem(QString::number(pe.getMonth())));
        ui->ta->setItem(i,5,new QTableWidgetItem(QString::number(pe.getBasic_salary())));
        ui->ta->setItem(i,6,new QTableWidgetItem(QString::number(pe.getPerf_salary())));
        ui->ta->setItem(i,7,new QTableWidgetItem(QString::number(pe.getBonus())));
        ui->ta->setItem(i,8,new QTableWidgetItem(QString::number(pe.getTotal_salary())));
        ui->ta->setItem(i,9,new QTableWidgetItem(QString::number(pe.getTax())));
        ui->ta->setItem(i,10,new QTableWidgetItem(QString::number(pe.getFinal_salary())));
        li1.moveNext();
    }
    ui->ta->show();
}
