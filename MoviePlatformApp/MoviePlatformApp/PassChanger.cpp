#include "PassChanger.h"

PassChanger::PassChanger(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

PassChanger::~PassChanger()
{}

bool PassChanger::isCurrentPassCorrect(const std::string & typedCurrentPass)
{
	std::string currentPass = loggedUser->getPassword();
	return currentPass == typedCurrentPass ? true : false;
}


void PassChanger::on_changePassButton_clicked()
{
	std::string currentPass = ui.currentPasLineEdit->text().toStdString();

	if (!isCurrentPassCorrect(currentPass))
	{
		QMessageBox::warning(this, "Warning!", "Your current password is missing or incorrect.");
		return;
	}

	std::regex pass_rule("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$");
	std::string newPass = ui.newPassLineEdit->text().toStdString();
	if (!regex_match(newPass, pass_rule)) {
		QMessageBox::warning(this, "Warning!", "New password is too weak. Use at least eight characters, one number and one letter.");
		return;
	}

	loggedUser->setPassword(newPass);
	auto user = loggedUser->getUser();
	database->replace<User>(user);
	QMessageBox::information(this, "Password", "Password was successfully updated!");
}