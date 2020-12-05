#include "show_staff.h"
#include "ui_show_staff.h"
#include "date.h"
#include "List.h"
#include "people.h"
#include "Note.h"
#include <QTableWidget>
#include <QMessageBox>


show_staff::show_staff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_staff)
{
    ui->setupUi(this);
}

show_staff::~show_staff()
{
    delete ui;
}

void show_staff::on_pushButton_clicked()
{
    int IDD=ui->spinBox_5->value();
    int beginyear=ui->spinBox->value();
    int beginmonth=ui->spinBox_2->value();
    int endyear=ui->spinBox_3->value();
    int endmonth=ui->spinBox_4->value();
    List<people>li0fpeo;
    List<Date>li0fdate("date.txt");
    li0fdate.reset();
    while(!li0fdate.is_empty()){
        Date da=li0fdate.popNote();
        std::string str=da.toDateString();
        const char *filename=str.c_str();
        List<people>li(filename);
        li0fpeo.tailInsertNote(searchidInList(li,IDD));
        li0fdate.moveNext();
    }
    List<people>li0fpeo2;
    drawPartList(li0fpeo,li0fpeo2,beginyear,beginmonth,endyear,endmonth);
    if(li0fpeo2.is_empty()){
        QMessageBox::warning(this,tr("注意"),tr("此区间无此人数据"));
    }
    else{
        ui->ta->clear();
        int length=li0fpeo2.length;
        ui->ta->setRowCount(length);
        ui->ta->setColumnCount(11);
        ui->ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QStringList header;
        header<<"编号"<<"姓名"<<"电话"<<"年份"<<"月份"<<"底薪"<<"绩效"<<"奖金"<<"应发工资"<<"扣税"<<"实发工资";
        ui->ta->setHorizontalHeaderLabels(header);
        li0fpeo2.reset();
        int i=0;
        for(i=0;i<length;++i){
            people pe=li0fpeo2.popNote();
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
            li0fpeo2.moveNext();
        }
        ui->ta->show();
    }
}
