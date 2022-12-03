#pragma once

#include <QMainWindow>
#include "ui_MovieView.h"
#include "DataBase.h"
#include "Movie.h"
#include "User.h"

class MovieView : public QMainWindow
{
	Q_OBJECT

public:
	MovieView(QWidget *parent = nullptr);
	~MovieView();
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

private:
	Ui::MovieViewClass ui;
	Database* database = Database::connect();
};
