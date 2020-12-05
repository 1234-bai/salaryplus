#include "sign_up.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sign_up *w=new Sign_up;
    w->setWindowTitle("登录界面");
    w->show();
    return a.exec();
}

