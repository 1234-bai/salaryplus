#ifndef PEOPLE_H
#define PEOPLE_H

#include "List.h"
#include "iostream"

class people
{
public:
    //构造函数
    people(int id=0,std::string name="xingming",std::string phone="1234",
        long long basic_salary=0,long long pref_salary=0,long long bonus=0,int year=0,int month=0);
    //以下为改变对象内容
    void changeBasic_salary(long long salary);
    void changePerf_salary(long long number);
    void changeBonus(long long bonus);
    void changeName(std::string name);
    void changePhone(std::string phone);
    void changeYear(int year);
    void changeMonth(int month);
    //以下为运算符重载，用于构成链表(主函数不使用)
    bool operator ==(const people &p)const;
    bool operator < (const people &p)const;
    void operator = (const people &p);
    bool operator != (const people &p)const;
    //这两个用于构成文件流（主函数不使用）。具体存文件是在list的函数里
    friend std::ostream& operator <<(std::ostream& out, people& p);
    friend std::istream& operator >>(std::istream& in, people& p);
    //以下为，获得对象中的内容
    int getid();
    long long getBasic_salary();
    long long getPerf_salary();
    std::string getName();
    std::string getPhone();
    long long getBonus();
    long long getTotal_salary();
    long long getTax();
    long long getFinal_salary();
    int getYear();
    int getMonth();
private:
    int id;		//编号
    std::string name;	//姓名
    std::string phone;	//电话号码
    long long basic_salary;	//底薪
    long long perf_salary;	//绩效
    long long bonus;	//奖金
    long long total_salary;		//应发工资
    long long tax;	//扣税，扣税的计算在构造函数（本文件9行）中完成
    long long final_salary;	//实发工资
    int year;	//年份
    int month;	//月份
};

//提取时，不同的提取条件
//当传入五个参数时，例如drawRule(pe,2020,4,2020,5),表示的是提取链表中日期在这两者之前的结点
//当传入参数为前四个的时候，例如drawRule(pe,2000,4000,-1)，表示的是提取链表中底薪在这两个数之间的结点
//以下为不同的c对应的意思：
//c==-1:底薪,c==-2绩效,c==-3奖金,c==-4应发工资,c==-5扣税,c==-6实发工资
bool drawRule(people pe,long long a, long long b, long long c, long long d=0);

//从from链表中按照上面规则提取出符合条件的结点组成to链表，from和to都需要在此函数的外面定义
//此函数中a,b,c,d的意思和drawRule函数意思相同
//如果from链表中没有符合条件的结点，则to链表为空（to.is_empty()函数，见List.h文件21行，122行）
void drawPartList(List<people>& from, List<people>& to, long long a, long long b, long long c, long long d=0);

//按照people的id在li链表中找的结点，返回note的指针，指向那个结点，没有这个id的话返回空指针
Note<people>* searchidInList(List<people>& li, int id);

//计算li链表中所有people的应发工资的综合，也就是会赋值给date的那个数
long long getsTotallSalary(List<people>& li);

bool basicrule(Note<people>*p1,Note<people>*p2);
bool perrule(Note<people>*p1,Note<people>*p2);
bool bonusrule(Note<people>*p1,Note<people>*p2);
bool totalrule(Note<people>*p1,Note<people>*p2);
bool taxrule(Note<people>*p1,Note<people>*p2);
bool finallrule(Note<people>*p1,Note<people>*p2);

#endif // PEOPLE_H
