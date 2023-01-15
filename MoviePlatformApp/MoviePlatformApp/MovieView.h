#pragma once

#include <QMainWindow>
#include "ui_MovieView.h"
#include "DataBase.h"
#include "Movie.h"
#include "User.h"
#include "MovieDashboard.h"
#include "InfoManager.h"
#include "PosterManager.h"

class MovieView : public QMainWindow
{
	Q_OBJECT

public:
	MovieView(int MovieId, QWidget *parent = nullptr);
	~MovieView();
	void setMovieView();
	void setMoviePoster(QPixmap image);
	void setMovieTitle(QString title);
	void setMovieRating();
	void setMovieDirector(QString director);
	void setMovieCast(QString cast);
	void setMovieCountry(QString country);
	void setMovieReleaseYear(QString release_year);
	void setMovieDescription(QString description);
	void setMovieListedIn(QString listed_in);
	void setMovieTypeAndDuration(QString type, QString duration);

private slots:
	void on_watchedButton_clicked();
	void on_wishlistButton_clicked();
	void assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData);
	void setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData);
	void similarTableDoubleClick(const QModelIndex&);

private:
	QWidget* m_parent;
	Ui::MovieViewClass ui;
	Database* database = Database::connect();
	LoggedUser* loggedUser = LoggedUser::login();
	int m_selectedMovieId;
	PosterManager posterManager;
	InfoManager infoManager;
	QStandardItemModel* m_similarMovieTable;
	std::vector<int> m_similarMovieIds;
};
