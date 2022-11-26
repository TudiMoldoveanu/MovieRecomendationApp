#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_LogInPage.h"
<<<<<<< HEAD
#include "DataBase.h"

class LogInPage : public QMainWindow, public Database
=======
#include"RegisterPage.h"
class LogInPage : public QMainWindow
>>>>>>> origin/develop
{
    Q_OBJECT

public:
    LogInPage(QWidget *parent = nullptr);
    ~LogInPage();
    
    bool verifiyLogin(std::string username, std::string password);

private slots:
    void on_logInButton_clicked();

private slots:
    void on_registerButton_clicked();
private:
    Ui::LogInPageClass ui;
    RegisterPage *registerPage;
};
