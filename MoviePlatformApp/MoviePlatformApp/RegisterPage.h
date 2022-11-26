#pragma once

#include <QMainWindow>
#include "ui_RegisterPage.h"

class RegisterPage : public QMainWindow
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

private slots:
	void on_pushButton_clicked();

private:
	Ui::RegisterPageClass ui;
};
