#include "sign_in.h"
#include "ui_sign_in.h"
#include "id.h"
#include "List.h"
#include "Note.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegExpValidator>

sign_in::sign_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    QRegExp rx1("^\\d{4,10}$");
    QRegExp rx2("^[a-zA-Z0-9]\\w{5,17}$");
    ui->lineEdit->setValidator(new QRegExpValidator(rx1,this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx2,this));
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::on_pushButton_clicked()
{
    List<ID>li("id0faddmin.txt");
    List<ID>l2("id0fstaff.txt");
    ID idd(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toStdString());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    Note<ID> *p=new Note<ID>(idd);
    Note<ID> *m=searchIDinList(l2,idd.getid());
    if(li.insertNote(p) && m==0) {
    QMessageBox::information(this,tr("注意"),tr("注册成功！"));
    li.List_to_file("id0faddmin.txt");
    }
    else QMessageBox::warning(this,tr("警告"),tr("账号已注册!"));
    close();
}
