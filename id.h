#ifndef ID_H
#define ID_H

#include <string>
#include "List.h"
#include "Note.h"

class ID
{
private:
    int id;
    std::string code;
public:
    ID(int id = 0, std::string code = "0");
    int getid();
    std::string getcode();
    bool operator < (const ID &p)const;
    void operator = (const ID &p);
    bool operator == (const ID &p)const;
    bool operator != (const ID &p)const;
    void changeCode(std::string code);
    friend std::ostream& operator <<(std::ostream& out, ID& p);
    friend std::istream& operator >>(std::istream& in, ID& p);
};

//通过返回值的不同判断，账户的存在状态（无账户；有账户，密码不对；有账户，密码正确）
int searchIDinList(List<ID>&li, int id, std::string code);
//找到ID的指针，修改密码
Note<ID>* searchIDinList(List<ID>& li, int id);

#endif // ID_H
