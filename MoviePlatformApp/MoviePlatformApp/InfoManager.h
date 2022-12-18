#pragma once
#include <QString>
#include <QList>
#include "Movie.h"
#include "DataBase.h"

class InfoManager
{
	Database* database = Database::connect();
public:
	QList<QString> getMovieInfo(const int& id);
};

