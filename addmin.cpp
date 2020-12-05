#include "addmin.h"
#include "ui_addmin.h"
#include <QInputDialog>
#include "show_staff.h"
#include "change_peo.h"
#include "List.h"
#include "Note.h"
#include "date.h"
#include <QMessageBox>
#include <QTableWidget>
#include "people.h"
#include "count.h"
#include "add.h"
#include "changeordelete.h"
#include <QDialog>

bool back_recover(const char*from,const char *to);

addmin::addmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmin)
{
    ui->setupUi(this);
}

addmin::~addmin()
{
    delete ui;
}

void addmin::on_search_clicked()
{
   show_staff *ss=new show_staff();
   ss->setWindowTitle(tr("查询界面"));
   ss->show();
}

void addmin::on_add_clicked()
{
    bool ok=false;
    int year0(2019),month0(1);
    Date da;
    da.getNowdate();
    int nowyear=da.getyear(),nowmonth=da.getmonth();
    std::string str=da.toDateString();
    const char * filename=str.c_str();
    std::ifstream fp(filename);
    if(fp.is_open()){
        int t1=QMessageBox::question(this,tr("注意"),tr("本月数据已存在，是否要继续录入？"),QMessageBox::Yes,QMessageBox::No);
        if(t1==QMessageBox::Yes) ok=true;   //新添加数据
    }
    else{
        if(nowyear==year0 && nowmonth==month0) ok=true; //新添加数据
        else {
            bool temp=(nowmonth==1);
            int lastyear=temp?(nowyear-1):nowyear;
            int lastmonth=temp?12:(nowmonth-1); //获得上月日期数据
            Date da1(lastyear,lastmonth);
            std::string str1=da1.toDateString();
            const char *filename1=str1.c_str();
            List<people>li;
            if(li.file_to_List(filename1)){
                li.reset();
                while (!li.is_empty()) {
                    li.nowPtr->data.changeYear(nowyear);
                    li.nowPtr->data.changeMonth(nowmonth);
                    li.moveNext();
                }
                li.reset();
                li.List_to_file(filename); //拷贝上月数据并存到文件里，现在只有一种情况就是起始月份没有文件了
                int t2=QMessageBox::question(this,tr("注意"),tr("上月数据拷贝完成，是否要进行更新操作？"),QMessageBox::Yes,QMessageBox::No);
                if(t2==QMessageBox::Yes){
                  li.reset();
                  bool run=true;
                  while(run && (!li.is_empty())){
                       run=false;
                       people pe=li.popNote();
                       changeORdelete *cod=new changeORdelete(pe,this);
                       cod->show();
                       if(cod->exec()==QDialog::Accepted) run=true;
                       li.moveNext();
                   }
                   int t3=QMessageBox::question(this,tr("注意"),tr("上月数据更新完成，是否要进行录入操作？"),QMessageBox::Yes,QMessageBox::No);
                   if(t3==QMessageBox::Yes) ok=true;
                   else{
                        li.clear();
                        li.file_to_List(filename);
                        da.changeSalary(getsTotallSalary(li));
                        List<Date>li0fda("date.txt");
                        li0fda.insertNote(new Note<Date>(da));
                        li0fda.List_to_file("date.txt");
                   }
                }
            }
            else QMessageBox::warning(this,tr("坏了"),tr("上月没数据"));
        }
    }
    if(ok){
        Add *ad=new Add(this);
        ad->setWindowTitle(tr("录入界面"));
        ad->show();
    }
}

void addmin::on_change_clicked()
{
    bool ok;
    int id=QInputDialog::getInt(this,tr("输入ID"),tr("请输出所要修改的ID"),0,0,2147483647,1,&ok);
    if(ok){
        change_peo *cp=new change_peo(id,tr("修改"),this);
        cp->setWindowTitle(tr("修改界面"));
    }
}

void addmin::on_deletee_clicked()
{
    bool ok;
    int id=QInputDialog::getInt(this,tr("输入ID"),tr("请输出所要删除的ID"),0,0,2147483647,1,&ok);
    if(ok){
        change_peo *cp=new change_peo(id,tr("删除"),this);
        cp->setWindowTitle(tr("删除界面"));
    }
}

void addmin::on_count_clicked()
{
   count *co=new count(this);
   co->setWindowTitle(tr("统计界面"));
   co->show();
}


void addmin::on_back_clicked()
{
    Date da1;
    da1.getNowdate();
    std::string str1=da1.toDateString();
    const char *filename1=str1.c_str();
    std::string str2="back";
    const char *filename2=str2.append(str1).c_str();
    if(!back_recover(filename1,filename2)) QMessageBox::warning(this,tr("错误"),tr("备份失败，本月数据不存在"));
    else{
        if(back_recover("date.txt","backdate.txt")) QMessageBox::information(this,tr("注意"),tr("备份成功"));
        else QMessageBox::warning(this,tr("错误"),tr("备份失败，本月日期数据不存在"));
    }
}

void addmin::on_recover_clicked()
{
    Date da1;
    da1.getNowdate();
    std::string str1=da1.toDateString();
    const char *filename1=str1.c_str();
    std::string str2="back";
    const char *filename2=str2.append(str1).c_str();
    if(!back_recover(filename2,filename1)) QMessageBox::warning(this,tr("错误"),tr("恢复失败，备份数据不存在"));
    else{
        if(back_recover("backdate.txt","date.txt")) QMessageBox::information(this,tr("注意"),tr("恢复成功"));
        else QMessageBox::warning(this,tr("错误"),tr("恢复失败，日期备份数据不存在"));
    }
}
