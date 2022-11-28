#pragma once

#include <QMainWindow>
#include "ui_MovieDashboard.h"
#include "DataBase.h"
#include <QApplication>
#include <QTableWidget>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class MovieDashboard : public QMainWindow
{
	Q_OBJECT

public:
	MovieDashboard(QWidget *parent = nullptr);
	~MovieDashboard();

	void loadMovieData();
	QPixmap download_from(const std::string& poster_url);

private:
	Ui::MovieDashboardClass ui;
	Database* database = Database::connect();
	QPixmap m_poster;
};
