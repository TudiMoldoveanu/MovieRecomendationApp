#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogInPage.h"
#include"RegisterPage.h"
class LogInPage : public QMainWindow
{
    Q_OBJECT

public:
    LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

private slots:
    void on_registerButton_clicked();
private:
    Ui::LogInPageClass ui;
    RegisterPage *registerPage;
};
