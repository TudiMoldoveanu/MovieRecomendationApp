#pragma once

#include <QMainWindow>
#include "ui_RegisterPage.h"
#include "DataBase.h"
#include "PreferencesPage.h"
enum ErrorCodes : uint8_t {
	EmptyFields,
	UsernameSize,
	WeakPassword,
	UsernameExists,
	PassNotMatchRetype
};

class RegisterPage : public QMainWindow
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

	bool validateRegisterForm(std::string username, std::string password,
		std::string fullname, std::string age,std::string retypePass);


	const char* errorCodeToString(const ErrorCodes& type);

private slots:
	void on_pushButton_clicked();
	void on_showPass_clicked();
	void on_hidePass_clicked();

private:
	Database* database = Database::connect(); // connecting the DB where using it (being singleton it will use the already instantiated object)
	Ui::RegisterPageClass ui;
	ErrorCodes m_errorCode;
	PreferencesPage *prefPage;
};
