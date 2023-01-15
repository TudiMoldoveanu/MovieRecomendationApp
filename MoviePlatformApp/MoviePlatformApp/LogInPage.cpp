#include "LogInPage.h"
#include "DataBase.h"

LogInPage::LogInPage(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    connect(ui.showPass, SIGNAL(clicked()), SLOT(on_showPass_clicked()));
    connect(ui.hidePass, SIGNAL(clicked()), SLOT(on_hidePass_clicked()));

    // hide loader label
    ui.loaderLabel->setVisible(false);
    ui.userLineEdit->setPlaceholderText("username");
    ui.passLineEdit->setPlaceholderText("password");
}

LogInPage::~LogInPage()
{}

bool LogInPage::verifiyLogin(std::string username, std::string password)
{
    auto allUsers = database->getAll<User>();

    for (const auto& user : allUsers) {
        if (user.getUsername() == username && user.getPassword() == password) {
            lUser = new User{ user.getId(), user.getUsername(), user.getPassword() };
                LoggedUser* loggedUser = LoggedUser::login(lUser);
            return true;
        }
    }
    return false;
}





void LogInPage::on_logInButton_clicked()
{
    // made the button unclickable in order to prevent multi clicks
    ui.logInButton->setEnabled(false);
    ui.logInButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");

    std::string username = ui.userLineEdit->text().toStdString();
    std::string  password = ui.passLineEdit->text().toStdString();

    if (username == "" || password == "")
    {
        QMessageBox::warning(this, "Warning!", "Please fill the empty fields!");  
    }
    else
    {
        if (verifiyLogin(username, password))
        {
            QMovie* loaderMovie = new QMovie("loader2.gif");
            ui.loaderLabel->setMovie(loaderMovie);
            ui.loaderLabel->show();
            loaderMovie->start();

            movieDashboard = new MovieDashboard(this);
            this->setVisible(false);
            movieDashboard->show();
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "Account does not exist! Please check your username and password!");
        }
    }

    // reset the button afterwards
    ui.logInButton->setEnabled(true);
    ui.logInButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
        "{\n"
        "border-radius:10px;\n"
        "}"));
}

void LogInPage::on_registerButton_clicked()
{
    registerPage = new RegisterPage(this);
    this->setVisible(false);
    registerPage->show();

    //to add recomendation functions
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