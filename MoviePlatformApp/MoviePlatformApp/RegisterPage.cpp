#include "RegisterPage.h"
#include "DataBase.h"
#include <iostream>
#include <QMessageBox>
#include <regex>

RegisterPage::RegisterPage(QWidget* parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);
	connect(ui.showPass, SIGNAL(clicked()), SLOT(on_showPass_clicked()));
	connect(ui.hidePass, SIGNAL(clicked()), SLOT(on_hidePass_clicked()));
}

RegisterPage::~RegisterPage()
{}




bool RegisterPage::validateRegisterForm(std::string username, std::string password, std::string fullname, std::string age)
{
	if (username.empty() || password.empty() || fullname.empty() || age.empty()) {
		m_errorCode = ErrorCodes::EmptyFields;
		return false;
	}

	if (username.size() < 3) {
		m_errorCode = ErrorCodes::UsernameSize;
		return false;
	}

	//Minimum eight characters, at least one letter and one number:
	std::regex pass_rule("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
	//

	if (!regex_match(password, pass_rule)) {
		m_errorCode = ErrorCodes::WeakPassword;
		return false;
	}

	// check if account already exists
	if (database->isRegistered(username))
	{
		m_errorCode = ErrorCodes::UsernameExists;
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
		return "Password is too weak. Use at least eight characters, one number and one letter.";
	case 3:
		return "Username already exists, try another one.";
	default:
		return "none";
	}
}
void RegisterPage::on_showPass_clicked()
{

	QString pass = ui.passLineEdit->text();
	ui.passLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	ui.passLineEdit->setText(pass);
	ui.passLineEdit_2->setEchoMode(QLineEdit::EchoMode::Normal);
	ui.passLineEdit_2->setText(pass);
	ui.showPass->setEnabled(false);
	ui.showPass->setVisible(false);
	ui.hidePass->setVisible(true);
	ui.hidePass->setEnabled(true);
}

void RegisterPage::on_hidePass_clicked()
{
	QString pass = ui.passLineEdit->text();
	ui.passLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	ui.passLineEdit->setText(pass);
	ui.passLineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);
	ui.passLineEdit_2->setText(pass);
	ui.hidePass->setEnabled(false);
	ui.hidePass->setVisible(false);
	ui.showPass->setEnabled(true);
	ui.showPass->setVisible(true);
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
		database->insert(user);
		database->insert(userInfo);
		prefPage = new PreferencesPage(this);
		this->setVisible(false);
		prefPage->show();
	}
	else {
		QMessageBox::information(this, "Register", errorCodeToString(m_errorCode));
	}
}