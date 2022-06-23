#include "mainwindow.h"
#include "loginpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage l;
    l.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
