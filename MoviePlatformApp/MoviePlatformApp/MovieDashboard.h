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
	MovieDashboard(std::optional<User> loggedUser, QWidget* parent = nullptr);
	~MovieDashboard();

	void setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData);
	QList<QString> getMovieInfo(const int& id);
	QPixmap getMoviePoster(const int& id, const std::string& size);
	QPixmap downloadMoviePoster(QUrl url);
	void assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData);

	std::string whiteSpaceReplace(std::string& s);
	void setHeader(QStandardItemModel* tableHeader);

	void setMovieDashboardData(const int& fromId, const int& toId);

private slots:
	void on_searchButton_clicked();
	void onMovieDoubleClick(const QModelIndex&);
	void on_nextPage_clicked();
	void on_previousPage_clicked();

private:
	Ui::MovieDashboardClass ui;
	Database* database = Database::connect();
	int m_movieIndex;
	std::optional<User> m_loggedUser;
	QStandardItemModel* tableData;
};
