#include "sign_up.h"
#include "ui_sign_up.h"
#include <QPushButton>
#include <QString>
#include "sign_in.h"
#include "id.h"
#include "Note.h"
#include "List.h"
#include "QMessageBox"
#include <QInputDialog>
#include "addmin.h"
#include "change_code.h"
#include "staff.h"
#include "QRegExpValidator"
#include <QPainter>

Sign_up::Sign_up(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sign_up)
{
    ui->setupUi(this);
    QString btnStyle = "\
        QPushButton{\
            color: rgb(38, 133, 227);\
            border:1px;\
        }\
        QPushButton:hover{\
            color: rgb(97, 179, 246);\
        }\
        QPushButton:pressed{\
            color: rgb(38, 133, 227);\
        }";
    ui->pushButton->setStyleSheet(btnStyle);
    ui->pushButton_2->setStyleSheet(btnStyle);
    QRegExp rx1("^\\d{4,10}$");
    QRegExp rx2("^[a-zA-Z0-9]\\w{5,17}$");
    ui->lineEdit->setValidator(new QRegExpValidator(rx1,this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx2,this));
}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::on_pushButton_clicked()
{
    change_code *cc=new change_code();
    cc->setWindowTitle(tr("修改密码"));
    cc->show();
}

void Sign_up::on_pushButton_2_clicked()
{
    sign_in *si=new sign_in();
    si->setWindowTitle(tr("注册界面"));
    si->show();
}

void Sign_up::on_pushButton_3_clicked()
{
    List<ID>li1("id0faddmin.txt");
    int id=ui->lineEdit->text().toInt();
    std::string code=ui->lineEdit_2->text().toStdString();
    int m=searchIDinList(li1,id,code);
    if(m==1){
        addmin *ad=new addmin();
        ad->setWindowTitle(tr("管理员界面"));
        ad->show();
    }
    else if(m==-1) QMessageBox::warning(this,tr("警告"),tr("密码输入错误！"));
    else{
        List<ID>li2("id0fstaff.txt");
        int n=searchIDinList(li2,id,code);
        if(n==1){
            staff *ss=new staff(id);
            ss->setWindowTitle(tr("工资"));
            ss->show();
        }
        else if(n==-1) QMessageBox::warning(this,tr("警告"),tr("密码输入错误！"));
        else QMessageBox::warning(this,tr("警告"),tr("无此账号！"));
    }
}

