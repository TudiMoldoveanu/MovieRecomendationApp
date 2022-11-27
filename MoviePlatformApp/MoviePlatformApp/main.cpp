#include "LogInPage.h"
#include <QtWidgets/QApplication>
#include "RegisterPage.h"
#include "PreferencesPage.h"
int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    LogInPage logInPage;
  //  RegisterPage registerPage;
    logInPage.show(); 
  //  registerPage.show();
    PreferencesPage preferencesPage;
    preferencesPage.show();
    return a.exec();
}
