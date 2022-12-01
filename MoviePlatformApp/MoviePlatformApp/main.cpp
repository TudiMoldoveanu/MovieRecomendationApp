#include "LogInPage.h"
#include <QtWidgets/QApplication>
#include "PreferencesPage.h"
#include "MovieDashboard.h"
int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    //LogInPage logInPage;
    //logInPage.show(); 
    //PreferencesPage preferencesPage;
    //preferencesPage.show();
    RegisterPage registerPage;
    registerPage.show();

    //MovieDashboard movieDashboard;
    //movieDashboard.show();
    return a.exec();
}
