#include "LogInPage.h"
#include "DataBase.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(on_pushButton_clicked()));
}

LogInPage::~LogInPage()
{}

bool LogInPage::verifiyLogin(std::string username, std::string password)
{
    auto allUsers = database->getAll<User>();

    for (const auto& user : allUsers) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;
        }
    }
    return false;
}


void LogInPage::on_logInButton_clicked()
{
    std::string username = ui.userLineEdit->text().toStdString();
    std::string  password = ui.passLineEdit->text().toStdString();

    if (verifiyLogin(username, password)) 
    {
        movieDashboard = new MovieDashboard(this);
        movieDashboard->show();
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "Account does not exist! Please check your username and password!");
    }
}

void LogInPage::on_registerButton_clicked()
{
    registerPage = new RegisterPage(this);
    registerPage->show();
    
}

void LogInPage::on_pushButton_clicked()
{
        QString pass = ui.passLineEdit->text();
        ui.passLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
         ui.passLineEdit->setText(pass); 
}

//TODO: add else case in where the pass and username doesn't match