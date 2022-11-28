#pragma once
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_LogInPage.h"
#include "DataBase.h"
#include "RegisterPage.h"

class LogInPage : public QMainWindow
{
    Q_OBJECT

public:
    LogInPage(QWidget *parent = nullptr);
    ~LogInPage();
    
    bool verifiyLogin(std::string username, std::string password);

private slots:
    void on_logInButton_clicked();
    void on_registerButton_clicked();
    void on_pushButton_clicked();

private:
    Database* database = Database::connect(); // connecting the DB where using it (being singleton it will use the already instantiated object)
    Ui::LogInPage ui;
    RegisterPage *registerPage;
};


