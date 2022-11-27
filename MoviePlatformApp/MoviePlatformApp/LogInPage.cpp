#include "LogInPage.h"
#include "DataBase.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
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

void LogInPage::on_logInButton_clicked() {
    std::string username = ui.userLineEdit->text().toStdString();
    std::string  password = ui.passLineEdit->text().toStdString();

    if (verifiyLogin(username, password)) {
        QMessageBox::information(this, "Login", "Logat cu succes");
    }

    //TODO: add else case in where the pass and username doesn't match

    //TODO: add functionality on register button
}
