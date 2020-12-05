#include "id.h"
#include <iostream>
#include <string>
#include <string.h>

ID::ID(int id, std::string code)
{
    this->id = id;
    this->code = code;
}

int ID::getid()
{
    return id;
}

std::string ID::getcode()
{
    return code;
}

bool ID::operator<(const ID &p) const
{
    return id<p.id;
}

void ID::operator=(const ID& p)
{
    id = p.id;
    code = p.code;
}

bool ID::operator==(const ID& p) const
{
    return id==p.id;
}

bool ID::operator!=(const ID& p) const
{
    return id!=p.id;
}

void ID::changeCode(std::string code)
{
    this->code = code;
}

std::ostream& operator<<(std::ostream& out, ID& p)
{
    out << '\n' << p.id << '\n' << p.code;
    return out;
}

std::istream& operator>>(std::istream& in, ID& p)
{
    in >> p.id;
    in.get();
    getline(in, p.code);
    return in;
}

//1表示密码和账号都正确；-1表示账号有，但是密码不正确；0表示无账号
int searchIDinList(List<ID> &li, int id, std::string code)
{
    li.reset();
    while (!li.is_empty()) {
        ID idd = li.popNote();
        if (idd.getid() == id) {
            if (idd.getcode() == code) return 1;
            else return -1;
        }
        li.moveNext();
    }
    li.reset();
    return 0;
}

//找到ID的确切指针,空指针代表没有，在函数的外面一定要加上判断
Note<ID>* searchIDinList(List<ID>& li, int id)
{
    li.reset();
    while (!li.is_empty()) {
        ID idd = li.popNote();
        if (idd.getid() == id) return li.nowPtr;
        li.moveNext();
    }
    li.reset();
    return 0;
}
