#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogInPage.h"

class LogInPage : public QMainWindow
{
    Q_OBJECT

public:
    LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

private:
    Ui::LogInPage ui;
};
