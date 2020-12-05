#include "change_code.h"
#include "ui_change_code.h"
#include "List.h"
#include "Note.h"
#include "id.h"
#include <QMessageBox>
#include <QRegExpValidator>

change_code::change_code(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_code)
{
    ui->setupUi(this);
    QRegExp rx1("^\\d{4,10}$");
    QRegExp rx2("^[a-zA-Z0-9]\\w{5,17}$");
    ui->lineEdit->setValidator(new QRegExpValidator(rx1,this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx2,this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(rx2,this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(rx2,this));
}

change_code::~change_code()
{
    delete ui;
}

void change_code::on_pushButton_clicked()
{
    List<ID>li1("id0faddmin.txt");
    List<ID>li2("id0fstaff.txt");
    int id=ui->lineEdit->text().toInt();
    std::string code=ui->lineEdit_2->text().toStdString();
    std::string code1=ui->lineEdit_3->text().toStdString();
    std::string code2=ui->lineEdit_4->text().toStdString();
    Note<ID> *m1=searchIDinList(li1,id);
    Note<ID> *m2=searchIDinList(li2,id);
    if(m1==0){
        if(m2==0) QMessageBox::warning(this,tr("警告"),tr("无此账号！"));
        else if(m2->data.getcode()==code){
            if(code1==code2){
                m2->data.changeCode(code1);
                li2.List_to_file("id0fstaff.txt");
                QMessageBox::information(this,tr("哈哈"),tr("修改成功！"));
                close();
            }
            else {
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                QMessageBox::warning(this,tr("警告"),tr("再次输入新密码有误，请重新输入"));
            }
        }
        else QMessageBox::warning(this,tr("警告"),tr("密码输入错误!请重新输入"));
    }
    else if(m1->data.getcode()==code){
        if(code1==code2){
            m1->data.changeCode(code1);
            li1.List_to_file("id0faddmin.txt");
            QMessageBox::information(this,tr("哈哈"),tr("修改成功！"));
            close();
        }
        else {
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            QMessageBox::warning(this,tr("警告"),tr("再次输入新密码有误，请重新输入"));
        }
    }
    else QMessageBox::warning(this,tr("警告"),tr("密码输入错误!请重新输入"));
}
