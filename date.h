#ifndef DATE_H
#define DATE_H


#include <iostream>
#include <string>
#include "List.h"

class Date
{
private:
    int year;
    int month;
    long long salary;
public:
    Date(int year = 0, int month = 0, int salary = 0);

    //将定义的这个date数据类型转化为现在的系统日期（2020年六月）
    void getNowdate();

    //将日期赋值给这个对象
    void initDate(int year, int month, int salary = 0);
    //改变
    void changeSalary(long long salary);
    //获得
    int getyear();
    int getmonth();
    long long getsalary();

    //将本date转化为字符串，然后后续操作转化为文件名。以下为程序示例
    //Date a;
    //a.getNowDate();得到当前系统时间
    //std::string str = a.toDateString();转化为string类型
    //const char* filename = str.c_str();转化为文件名
    std::string toDateString();

    //运算符重载
    bool operator ==(const Date& p)const;
    bool operator !=(const Date& p)const;
    bool operator < (const Date& p)const;
    void operator =(const Date& p);
    friend std::ostream& operator <<(std::ostream& out, Date& p);
    friend std::istream& operator >>(std::istream& in, Date& p);
};

//在date的li链表中根据date数据类型找到结点指针，并进行修改salary的后续操作
Note<Date>* searchDate(List<Date>& li, Date& da);
//提取链表中符合年份的这一部分
void drawPartDateList(List<Date>&from, List<Date> &to, int Year);

#endif // DATE_H
