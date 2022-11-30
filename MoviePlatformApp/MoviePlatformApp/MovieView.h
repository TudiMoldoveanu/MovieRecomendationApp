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

private:
	Ui::MovieViewClass ui;
	Database* database = Database::connect();
};
