#include "RegisterPage.h"
#include "DataBase.h"
#include <iostream>

RegisterPage::RegisterPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_pushButton_clicked() {
	QString username = ui.userLineEdit->text();
	QString password = ui.passLineEdit->text();
	QString fullname = ui.nameLineEdit->text();
	QString age = ui.ageSpinBox->text();

	Database *db = new Database;

	User user{ -1, username.toStdString(), password.toStdString() };
	db->insertIntoUser(user);

	UserInfo userInfo{ user.getId(), fullname.toStdString(), age.toStdString() };
	db->insertIntoUserInfo(userInfo);
}