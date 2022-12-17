#pragma once

#include <QDialog>
#include <regex>
#include <QMessageBox>
#include "ui_PassChanger.h"
#include "DataBase.h"
#include "LoggedUser.h"

class PassChanger  : public QDialog
{
	Q_OBJECT

public:
	PassChanger(QWidget *parent);
	~PassChanger();

private:
	Ui::ChangePass ui;
	Database* database = Database::connect();
	LoggedUser* loggedUser = LoggedUser::login();

private slots:
	void on_changePassButton_clicked();

private:
	bool isCurrentPassCorrect(const std::string& typedCurrentPass);
};
