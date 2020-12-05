#include <QTableWidget>
#include "List.h"
#include "Note.h"
#include "date.h"
#include "people.h"
#include <QMessageBox>

void display(List<Date>&li0fda)
{
    int length=li0fda.length;
    QTableWidget *ta=new QTableWidget(length+1,3);
    ta->setWindowTitle("总结算表");
    ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ta->resize(400,300);
    QStringList header;
    header<<"年份"<<"月份"<<"支出";
    ta->setHorizontalHeaderLabels(header);
    int i=0;
    long long salary(0);
    for(i=0;i<length;++i){
        Date da=li0fda.popNote();
        ta->setItem(i,0,new QTableWidgetItem(QString::number(da.getyear())));
        ta->setItem(i,1,new QTableWidgetItem(QString::number(da.getmonth())));
        ta->setItem(i,2,new QTableWidgetItem(QString::number(da.getsalary())));
        salary+=da.getsalary();
        li0fda.moveNext();
    }
    ta->setItem(i,0,new QTableWidgetItem("总支出"));
    ta->setItem(i,1,new QTableWidgetItem(QString::number(salary)));
    li0fda.reset();
    ta->show();
}

void display(List<people>&li0fpeo2)
{

    QTableWidget *ta=new QTableWidget(li0fpeo2.length,11);
    ta->setWindowTitle("人员工资一览表");
    ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ta->resize(1500,1000);
    QStringList header;
    header<<"编号"<<"姓名"<<"电话"<<"年份"<<"月份"<<"底薪"<<"绩效"<<"奖金"<<"应发工资"<<"扣税"<<"实发工资";
    ta->setHorizontalHeaderLabels(header);
    li0fpeo2.reset();
    int i=0;
    for(i=0;i<li0fpeo2.length;++i){
        people pe=li0fpeo2.popNote();
        ta->setItem(i,0,new QTableWidgetItem(QString::number(pe.getid())));
        ta->setItem(i,1,new QTableWidgetItem(QString::fromStdString(pe.getName())));
        ta->setItem(i,2,new QTableWidgetItem(QString::fromStdString(pe.getPhone())));
        ta->setItem(i,3,new QTableWidgetItem(QString::number(pe.getYear())));
        ta->setItem(i,4,new QTableWidgetItem(QString::number(pe.getMonth())));
        ta->setItem(i,5,new QTableWidgetItem(QString::number(pe.getBasic_salary())));
        ta->setItem(i,6,new QTableWidgetItem(QString::number(pe.getPerf_salary())));
        ta->setItem(i,7,new QTableWidgetItem(QString::number(pe.getBonus())));
        ta->setItem(i,8,new QTableWidgetItem(QString::number(pe.getTotal_salary())));
        ta->setItem(i,9,new QTableWidgetItem(QString::number(pe.getTax())));
        ta->setItem(i,10,new QTableWidgetItem(QString::number(pe.getFinal_salary())));
        li0fpeo2.moveNext();
    }
    ta->show();
}

void display(Note<people>*p)
{
    QTableWidget *ta=new QTableWidget(1,11);
    ta->setWindowTitle("人员工资一览");
    ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ta->resize(500,1000);
    QStringList header;
    header<<"编号"<<"姓名"<<"电话"<<"年份"<<"月份"<<"底薪"<<"绩效"<<"奖金"<<"应发工资"<<"扣税"<<"实发工资";
    ta->setHorizontalHeaderLabels(header);
    people pe=p->data;
    ta->setItem(0,0,new QTableWidgetItem(QString::number(pe.getid())));
    ta->setItem(0,1,new QTableWidgetItem(QString::fromStdString(pe.getName())));
    ta->setItem(0,2,new QTableWidgetItem(QString::fromStdString(pe.getPhone())));
    ta->setItem(0,3,new QTableWidgetItem(QString::number(pe.getYear())));
    ta->setItem(0,4,new QTableWidgetItem(QString::number(pe.getMonth())));
    ta->setItem(0,5,new QTableWidgetItem(QString::number(pe.getBasic_salary())));
    ta->setItem(0,6,new QTableWidgetItem(QString::number(pe.getPerf_salary())));
    ta->setItem(0,7,new QTableWidgetItem(QString::number(pe.getBonus())));
    ta->setItem(0,8,new QTableWidgetItem(QString::number(pe.getTotal_salary())));
    ta->setItem(0,9,new QTableWidgetItem(QString::number(pe.getTax())));
    ta->setItem(0,10,new QTableWidgetItem(QString::number(pe.getFinal_salary())));
    ta->show();
}
