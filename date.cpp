#include "date.h"
#include <time.h>
#include <string.h>
#include <cstdlib>
#include <string>

Date::Date(int year, int month, int salary)
{
    this->year = year;
    this->month = month;
    this->salary = salary;
}

void Date::getNowdate()
{
    time_t t = time(NULL);
    tm local = *(localtime(&t));
    year = local.tm_year+1900;
    month = local.tm_mon+1;
}

void Date::initDate(int year, int month, int salary)
{
    this->year = year;
    this->month = month;
    this->salary = salary;
}

void Date::changeSalary(long long salary)
{
    this->salary = salary;
}

int Date::getyear()
{
    return year;
}

int Date::getmonth()
{
    return month;
}

long long Date::getsalary()
{
    return salary;
}

std::string  Date::toDateString()
{
    char t[100] = { 0 };
    sprintf(t, "%04d%02d.txt", year, month);
    std::string str(t);
    return str;
}

bool Date::operator==(const Date& p) const
{
    return (year==p.year)&&(month==p.month);
}

bool Date::operator!=(const Date& p) const
{
    return (year!=p.year)||(month!=p.month);
}

bool Date::operator<(const Date& p) const
{
    if (year != p.year) return year < p.year;
    return month<p.month;
}

void Date::operator=(const Date& p)
{
    month = p.month;
    year = p.year;
    salary = p.salary;
}

std::ostream& operator<<(std::ostream& out, Date& p)
{
    out << '\n' << p.year << '\n' << p.month << '\n' << p.salary;
    return out;
}

std::istream& operator>>(std::istream& in, Date& p)
{
    in >> p.year >> p.month >> p.salary;
    return in;
}

Note<Date>* searchDate(List<Date>& li, Date& da)
{
    li.reset();
    while (!li.is_empty()) {
        Date dd = li.popNote();
        if (dd == da) return li.nowPtr;
        li.moveNext();
    }
    li.reset();
    return nullptr;
}

void drawPartDateList(List<Date>&from, List<Date> &to, int Year)
{
    from.reset();
    while (!from.is_empty()) {
        Date da = from.popNote();
        if (da.getyear()==Year) to.tailInsertNote(new Note<Date>(da));
        from.moveNext();
    }
    from.reset();
    to.reset();
}
