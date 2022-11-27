#pragma once

#include <QMainWindow>
#include "ui_RegisterPage.h"
#include "DataBase.h"

enum ErrorCodes : uint8_t {
	EmptyFields,
	UsernameSize,
	WeakPassword,
};

class RegisterPage : public QMainWindow
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

	bool validateRegisterForm(std::string username, std::string password,
		std::string fullname, std::string age);

	const char* errorCodeToString(const ErrorCodes& type);

private slots:
	void on_pushButton_clicked();

private:
	Ui::RegisterPageClass ui;
	ErrorCodes m_errorCode;
};
