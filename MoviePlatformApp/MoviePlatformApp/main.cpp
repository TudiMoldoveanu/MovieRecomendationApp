#include "LogInPage.h"
#include <QtWidgets/QApplication>
#include "RegisterPage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInPage logInPage;
    RegisterPage registerPage;
    logInPage.show(); 
    registerPage.show();
    return a.exec();
}
