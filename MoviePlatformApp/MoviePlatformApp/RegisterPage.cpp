#include "RegisterPage.h"
#include "DataBase.h"
#include <iostream>
#include <QMessageBox>
#include <regex>

RegisterPage::RegisterPage(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

RegisterPage::~RegisterPage()
{}

bool RegisterPage::validateRegisterForm(std::string username, std::string password, std::string fullname, std::string age)
{
	//Minimum eight characters, at least one letter and one number:
	std::regex pass_rule("^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$");
	//
	if (username.empty() || password.empty() || fullname.empty() || age.empty()) {
		m_errorCode = ErrorCodes::EmptyFields;
		return false;
	}
	if (username.size() < 3) {
		m_errorCode = ErrorCodes::UsernameSize;
		return false;
	}
	if (regex_match(password, pass_rule)){
		m_errorCode = ErrorCodes::WeakPassword;
		return false;
	}
	return true;
}

const char* RegisterPage::errorCodeToString(const ErrorCodes& type)
{
	switch (type) {
	case 0:
		return "One of the fields is empty!";
	case 1:
		return "Username too short.";
	case 2:
		return "Password is too weak.(Use at least eight characters, one number and one letter)";
	default:
		return "none";
	}
}

void RegisterPage::on_pushButton_clicked() {
	std::string username = ui.userLineEdit->text().toStdString();
	std::string  password = ui.passLineEdit->text().toStdString();
	std::string  fullname = ui.nameLineEdit->text().toStdString();
	std::string  age = ui.ageSpinBox->text().toStdString();

	if (validateRegisterForm(username, password, fullname, age)) {
		User user{ -1, username, password };
		UserInfo userInfo{ user.getId(), fullname, age };

		//insert
		/*Database::insertIntoUser(user);
		Database::insertIntoUserInfo(userInfo);*/
	}
	else {
		QMessageBox::information(this, "Register", errorCodeToString(m_errorCode));
	}
}