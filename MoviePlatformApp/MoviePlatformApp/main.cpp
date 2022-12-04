#include "LogInPage.h"
#include <QtWidgets/QApplication>
#include "PreferencesPage.h"
int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    LogInPage logInPage;
    logInPage.show(); 

    return a.exec();
}
