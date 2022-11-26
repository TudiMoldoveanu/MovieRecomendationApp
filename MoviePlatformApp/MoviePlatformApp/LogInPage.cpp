#include "LogInPage.h"
#include "DataBase.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

LogInPage::~LogInPage()
{}
<<<<<<< HEAD

bool LogInPage::verifiyLogin(std::string username, std::string password)
{
    auto allUsers = Database::getStorage().get_all<User>();

    for (auto& user : allUsers) {
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
}

=======
void LogInPage::on_registerButton_clicked()
{
    
    registerPage = new RegisterPage(this);
    registerPage->show();
    
 }
>>>>>>> origin/develop
