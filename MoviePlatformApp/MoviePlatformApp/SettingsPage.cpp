#include "SettingsPage.h"

SettingsPage::SettingsPage(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_currentName = database->getById<UserInfo>(loggedUser->getId()).getFullName();
	ui.nameLineEdit->setText(QString::fromStdString(m_currentName));
}

SettingsPage::~SettingsPage()
{}

void SettingsPage::on_changePassButton_clicked()
{
	PassChanger* passChanger = new PassChanger(this);
	passChanger->setVisible(true);
}

void SettingsPage::on_changeNameButton_clicked()
{
	std::string newName = ui.nameLineEdit->text().toStdString();

	if (newName == m_currentName)
	{
		QMessageBox::warning(this, "Warning!", "You already have this name.");
		return;
	}

	auto userInfo = database->getById<UserInfo>(loggedUser->getId());
	userInfo.setFullName(newName);
	database->replace<UserInfo>(userInfo);
	m_currentName = newName;
	MovieDashboard::uiDashboard.yourNameLabel->setText(QString::fromStdString(newName + "!"));
	QMessageBox::information(this, "Name", "Name was successfully updated!");
}
