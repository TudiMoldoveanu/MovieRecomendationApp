#include "LogInPage.h"
#include "DataBase.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    connect(ui.showPass, SIGNAL(clicked()), SLOT(on_showPass_clicked()));
    connect(ui.hidePass, SIGNAL(clicked()), SLOT(on_hidePass_clicked()));
}

LogInPage::~LogInPage()
{}

bool LogInPage::verifiyLogin(std::string username, std::string password)
{
    auto allUsers = database->getAll<User>();

    for (const auto& user : allUsers) {
        if (user.getUsername() == username && user.getPassword() == password) {
            if (!loggedUser.has_value())
                loggedUser = user;
            return true;
        }
    }
    return false;
}

const std::optional<User>& LogInPage::getLoggedUser()
{
    return loggedUser;
}


void LogInPage::on_logInButton_clicked()
{
    std::string username = ui.userLineEdit->text().toStdString();
    std::string  password = ui.passLineEdit->text().toStdString();
    if (username == "" | password == "")
    {
        QMessageBox::warning(this, "Warning!", "Please fill the empty fields!");
        return;
    }

    if (verifiyLogin(username, password)) 
    {
       
        ui.loaderLabel->show();
        ui.loaderMovie->start();
        ui.logInButton->setEnabled(false);
        ui.logInButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
        movieDashboard = new MovieDashboard(loggedUser, this);
        this->setVisible(false);
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
    this->setVisible(false);
    registerPage->show();
    
}

void LogInPage::on_showPass_clicked()
{
    QString pass = ui.passLineEdit->text();
    ui.passLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
    ui.passLineEdit->setText(pass);
    ui.showPass->setEnabled(false);
    ui.showPass->setVisible(false);
    ui.hidePass->setVisible(true);
    ui.hidePass->setEnabled(true);
}

void LogInPage::on_hidePass_clicked()
{
    QString pass = ui.passLineEdit->text();
    ui.passLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    ui.passLineEdit->setText(pass);
    ui.hidePass->setEnabled(false);
    ui.hidePass->setVisible(false);
    ui.showPass->setEnabled(true);
    ui.showPass->setVisible(true);
}

std::optional<User> LogInPage::loggedUser;

//TODO: add else case in where the pass and username doesn't match