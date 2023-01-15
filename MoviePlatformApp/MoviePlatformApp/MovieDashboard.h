#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include "ui_MovieDashboard.h"
#include "DataBase.h"
#include "LoggedUser.h"	
#include "MovieView.h"
#include <QApplication>
#include <QTableWidget>
#include <QByteArray>
#include <QList>
#include "Movie.h"
#include "UserWishlist.h"
#include "SettingsPage.h"
#include "SimilarMoviesEngine.h"
#include "PosterManager.h"
#include "InfoManager.h"
#include <ctime>
#include"RecomendationEngine.h"


class MovieDashboard : public QMainWindow
{
	Q_OBJECT

public:
	MovieDashboard(QWidget* parent = nullptr);
	~MovieDashboard();

	void setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData);
	void assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData);

	void setMovieDashboardData(const int& fromId, const int& toId);
	void setMovieWishlistData();
	void setMovieWatchedData();
	void setRecommendedMoviesData();
	void setMyProfileData();
	void setMovieView(const int& selectedMovieId);
	std::vector<int> getPreferencesRecommendations(std::vector<Movie> prefMovies);

	template<class T>
	QStandardItemModel* setModelData(QStandardItemModel* tableData) {
		tableData = new QStandardItemModel();
		std::vector<int> movieIds = database->getSavedMovies<T>(loggedUser->getId());

		for (int i = 0; i < movieIds.size(); i++) {
			QPixmap moviePoster = posterManager.getMoviePoster(movieIds[i], "154");
			QList<QString> movieInfo = infoManager.getMovieInfo(movieIds[i]);

			QStandardItem* item = new QStandardItem;
			item->setData(moviePoster, Qt::DisplayRole);
			item->setData(movieInfo[1], Qt::UserRole);
			tableData->setItem(0, i, item);
		}

		return tableData;
	}

private slots:
	void on_searchButton_clicked();
	void dashboardMovieDoubleClick(const QModelIndex&);
	void wishlistMovieDoubleClick(const QModelIndex&);
	void watchedMovieDoubleClick(const QModelIndex&); 
	void recommendedMovieDoubleClick(const QModelIndex&);
	void tabSelected();
	void on_nextPage_clicked();
	void on_previousPage_clicked();
	void on_settingsButton_clicked();

private:
	Database* database = Database::connect();
	LoggedUser* loggedUser = LoggedUser::login();
	int m_movieIndex;
	int m_randomNumber;
	std::vector<Movie> m_allMovies;
	std::vector<int> m_searchMovies;
	std::set<int> m_recommendedMoviesIds;
	QStandardItemModel* m_dashboardTableData;
	QStandardItemModel* m_wishlistTableData;
	QStandardItemModel* m_watchedTableData;
	QStandardItemModel* m_myProfileData;
	QStandardItemModel* m_recommendTableData;
	const int k_paginateNr = 32;
	const int k_noOfMovies = 8807;
	const int k_cols = 8;
	int k_currentPage = 0;
	int k_rows = 0;
	PosterManager posterManager;
	InfoManager infoManager;
	int randomIndex();

public:
	static Ui::MovieDashboardClass uiDashboard;
	Ui::MovieDashboardClass ui;
};
