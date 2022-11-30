#pragma once

#include <QMainWindow>
#include "ui_MovieDashboard.h"
#include "DataBase.h"
#include "MovieView.h"
#include <QApplication>
#include <QTableWidget>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardItemModel>

class MovieDashboard : public QMainWindow
{
	Q_OBJECT

public:
	MovieDashboard(QWidget *parent = nullptr);
	~MovieDashboard();

	void loadMovieData(int fromIndex, int toIndex, std::string optiune);
	QPixmap downloadFrom(const std::string& poster_url, const std::string& title, const std::string& size);
	std::string whitespaceReplace(std::string& s);
	void setHeader();

private slots:
	void on_searchButton_clicked();
	void on_loadMoreButton_clicked();
	void onMovieDoubleClick(const QModelIndex&);

private:
	Ui::MovieDashboardClass ui;
	Database* database = Database::connect();
	std::vector<Movie, std::allocator<Movie>> allMovies;
	int movieIndex;
	QStandardItemModel* model;
};
