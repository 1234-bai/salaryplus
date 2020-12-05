#include "count.h"
#include "ui_count.h"
#include <QInputDialog>
#include "date.h"
#include "people.h"
#include <QMessageBox>
#include "show_salary.h"
#include <fstream>

void display(Note<people>*p);

count::count(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::count)
{
    ui->setupUi(this);
    List<Date>li0fda("date.txt");
    if(li0fda.is_empty()){
        QMessageBox::warning(this,tr("警告"),tr("无数据"));
    }
    else{
        int length=li0fda.length;
        ui->ta->setRowCount(length+1);
        ui->ta->setColumnCount(3);
        ui->ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QStringList header;
        header<<"年份"<<"月份"<<"支出";
        ui->ta->setHorizontalHeaderLabels(header);
        int i=0;
        long long salary(0);
        for(i=0;i<length;++i){
            Date da=li0fda.popNote();
            ui->ta->setItem(i,0,new QTableWidgetItem(QString::number(da.getyear())));
            ui->ta->setItem(i,1,new QTableWidgetItem(QString::number(da.getmonth())));
            ui->ta->setItem(i,2,new QTableWidgetItem(QString::number(da.getsalary())));
            salary+=da.getsalary();
            if(i==length-1) ui->spinBox->setRange(2019,li0fda.nowPtr->data.getyear());
            li0fda.moveNext();
        }
        ui->ta->setItem(i,0,new QTableWidgetItem("总支出"));
        ui->ta->setItem(i,1,new QTableWidgetItem(QString::number(salary)));
        li0fda.reset();
        ui->ta->show();
    }
}

count::~count()
{
    delete ui;
}

void count::on_pushButton_clicked()
{
    int year=ui->spinBox->value();
    int month=ui->spinBox_2->value();
    List<Date>li0fda("date.txt");
    if(li0fda.is_empty()){
        QMessageBox::warning(this,tr("警告"),tr("无数据"));
    }
    else{
        if(month==0){
            List<Date>la;
            drawPartDateList(li0fda,la,year);
            if(la.is_empty()){
                QMessageBox::warning(this,tr("警告"),tr("此年度无数据"));
            }
            else{
                ui->ta->clear();
                int length=la.length;
                ui->ta->setRowCount(length+1);
                ui->ta->setColumnCount(3);
                ui->ta->setEditTriggers(QAbstractItemView::NoEditTriggers);
                QStringList header;
                header<<"年份"<<"月份"<<"支出";
                ui->ta->setHorizontalHeaderLabels(header);
                int i=0;
                long long salary(0);
                for(i=0;i<length;++i){
                    Date da=la.popNote();
                    ui->ta->setItem(i,0,new QTableWidgetItem(QString::number(da.getyear())));
                    ui->ta->setItem(i,1,new QTableWidgetItem(QString::number(da.getmonth())));
                    ui->ta->setItem(i,2,new QTableWidgetItem(QString::number(da.getsalary())));
                    salary+=da.getsalary();
                    la.moveNext();
                }
                ui->ta->setItem(i,0,new QTableWidgetItem("总支出"));
                ui->ta->setItem(i,1,new QTableWidgetItem(QString::number(salary)));
                la.reset();
                ui->ta->show();
            }
        }
        else{
            Date da(year,month);
            std::string st=da.toDateString();
            const char *filename=st.c_str();
            std::ifstream fp(filename);
            if(fp.is_open()){
            show_salary *ss=new show_salary(year,month);
            ss->show();
            }
            else QMessageBox::warning(this,tr("警告"),tr("此月份无数据"));
        }
    }
}
