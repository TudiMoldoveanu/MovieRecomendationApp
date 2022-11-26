#include "LogInPage.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

LogInPage::~LogInPage()
{}
void LogInPage::on_registerButton_clicked()
{
    
    registerPage = new RegisterPage(this);
    registerPage->show();
    
 }