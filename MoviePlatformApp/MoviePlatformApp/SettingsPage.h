#pragma once
#include "ui_SettingsPage.h"
#include <QDialog>
#include <QMessageBox>
#include "DataBase.h"
#include "LoggedUser.h"
#include "PassChanger.h"
#include "MovieDashboard.h"

class SettingsPage  : public QDialog
{
	Q_OBJECT

public:
	SettingsPage(QWidget *parent = nullptr);
	~SettingsPage();

private:
	Ui::SettingsPage ui;
	Database* database = Database::connect();
	LoggedUser* loggedUser = LoggedUser::login();

private slots:
	void on_changeNameButton_clicked();
	void on_changePassButton_clicked();

private:
	std::string m_currentName;
};
