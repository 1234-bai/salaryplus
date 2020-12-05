#include "people.h"

double tax_rate = 0.03;	//定义税率

people::people(int id, std::string name, std::string phone, long long basic_salary, long long perf_salary, long long bonus, int year, int month)
{
    this->id = id;
    this->name = name;
    this->phone = phone;
    this->basic_salary = basic_salary;
    this->perf_salary = perf_salary;
    this->bonus = bonus;
    this->year = year;
    this->month = month;
    this->total_salary = basic_salary + perf_salary + bonus;
    this->tax = (long long)(this->total_salary * tax_rate);
    this->final_salary = this->total_salary - this->tax;
}

void people::changeBasic_salary(long long salary)
{
    this->basic_salary = salary;
    this->total_salary = this->basic_salary + this->perf_salary + this->bonus;
    this->tax = (long long)(this->total_salary * tax_rate);
    this->final_salary = this->total_salary - this->tax;
}


void people::changePerf_salary(long long number)
{
    this->perf_salary = number;
    this->total_salary = this->basic_salary + this->perf_salary + this->bonus;
    this->tax = (long long)(this->total_salary * tax_rate);
    this->final_salary = this->total_salary - this->tax;
}

void people::changeBonus(long long bonus)
{
    this->bonus = bonus;
    this->total_salary = this->basic_salary + this->perf_salary + this->bonus;
    this->tax = (long long)(this->total_salary * tax_rate);
    this->final_salary = this->total_salary - this->tax;
}

void people::changeName(std::string name)
{
    this->name = name;
}

void people::changePhone(std::string phone)
{
    this->phone = phone;
}

void people::changeYear(int year)
{
    this->year = year;
}

void people::changeMonth(int month)
{
    this->month = month;
}

bool people::operator==(const people& p) const
{
    return id==p.id;
}

bool people::operator<(const people &p)const
{
    return id < p.id;
}

void people::operator=(const people &p)
{
    id = p.id;
    name = p.name;
    phone = p.phone;
    basic_salary = p.basic_salary;
    perf_salary = p.perf_salary;
    bonus = p.bonus;
    total_salary = p.total_salary;
    tax = p.tax;
    final_salary = p.final_salary;
    year = p.year;
    month = p.month;
}

bool people::operator!=(const people &p) const
{
    return id != p.id;
}

int people::getid()
{
    return id;
}

long long people::getBasic_salary()
{
    return basic_salary;
}

long long people::getPerf_salary()
{
    return perf_salary;
}

std::string people::getName()
{
    return name;
}

std::string people::getPhone()
{
    return phone;
}

long long people::getBonus()
{
    return bonus;
}

long long people::getTotal_salary()
{
    return total_salary;
}

long long people::getTax()
{
    return tax;
}

long long people::getFinal_salary()
{
    return final_salary;
}

int people::getYear()
{
    return year;
}

int people::getMonth()
{
    return month;
}

std::ostream& operator<<(std::ostream& out, people& p)
{
    out << '\n' << p.id << '\n' << p.name << '\n' << p.phone;
    out << '\n' << p.year << '\n' << p.month;
    out << '\n' << p.basic_salary << '\n' << p.perf_salary << '\n' << p.bonus;
    out << '\n' << p.total_salary << '\n' << p.tax << '\n' << p.final_salary;
    return out;
}

std::istream& operator>>(std::istream& in, people& p)
{
    in >> p.id;
    in.get();
    getline(in,p.name);
    in >> p.phone;
    in >> p.year >> p.month;
    in >> p.basic_salary >> p.perf_salary >> p.bonus >> p.total_salary >> p.tax >> p.final_salary;
    return in;
}

bool drawRule(people pe, long long beginYear, long long beginMonth, long long endYear, long long endMonth)
{
    if (endMonth > 0) {
        int year = pe.getYear();
        int month = pe.getMonth();
        if (year == beginYear){
            if(year == endYear) return (month>=beginMonth)&&(month<=endMonth);
            return month >= beginMonth;
        }
        if (year == endYear) return month <= endMonth;
        return (year > beginYear) && (year < endYear);
    }
    else {
        long long salary(-1);
        switch (endYear) {
        case(-1):
            salary =pe.getBasic_salary();
            break;
        case(-2):
            salary =pe.getPerf_salary();
            break;
        case(-3):
            salary = pe.getBonus();
            break;
        case(-4):
            salary = pe.getTotal_salary();
            break;
        case(-5):
            salary = pe.getTax();
            break;
        case(-6):
            salary = pe.getFinal_salary();
            break;
        default:
            break;
        }
        return (salary <= beginMonth) && (salary >= beginYear);
    }
}

void drawPartList(List<people>&from, List<people> &to, long long beginYear, long long beginMonth, long long endYear, long long endMonth)
{
    from.reset();
    while (!from.is_empty()) {
        people pe = from.popNote();
        if (drawRule(pe, beginYear, beginMonth, endYear, endMonth)) to.tailInsertNote(new Note<people>(pe));
        from.moveNext();
    }
    from.reset();
    to.reset();
}

Note<people>* searchidInList(List<people>& li, int id)
{
    li.reset();
    while (!li.is_empty()) {
        people pe = li.popNote();
        if (pe.getid() == id) return li.nowPtr;
        li.moveNext();
    }
    li.reset();
    return 0;
}

long long getsTotallSalary(List<people>& li)
{
    long long salary(0);
    li.reset();
    while (!li.is_empty()) {
        people pe = li.popNote();
        salary += pe.getTotal_salary();
        li.moveNext();
    }
    li.reset();
    return salary;
}

bool basicrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getBasic_salary();
    long long n=p2->data.getBasic_salary();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}

bool perrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getPerf_salary();
    long long n=p2->data.getPerf_salary();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}

bool bonusrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getBonus();
    long long n=p2->data.getBonus();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}

bool totalrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getTotal_salary();
    long long n=p2->data.getTotal_salary();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}

bool taxrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getTax();
    long long n=p2->data.getTax();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}

bool finallrule(Note<people>*p1,Note<people>*p2)
{
    long long m=p1->data.getFinal_salary();
    long long n=p2->data.getFinal_salary();
    if(m!=n) return m<n;
    else return p1->data.getid() < p2->data.getid();
}
