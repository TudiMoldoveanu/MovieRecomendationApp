#include "LogInPage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInPage logInPage; 
    logInPage.show();  
    return a.exec();
}
