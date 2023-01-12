#include "InfoManager.h"

QList<QString> InfoManager::getMovieInfo(const int& id)
{
	Movie movie = database->getById<Movie>(id);

	QList<QString> movieInfo = {
		QString::fromStdString(std::move(*movie.getType())),
		QString::fromStdString(std::move(*movie.getTitle())),
		QString::fromStdString(std::move(*movie.getDirector())) ,
		QString::fromStdString(std::move(*movie.getCast())),
		QString::fromStdString(std::move(*movie.getCountry())),
		QString::fromStdString(std::move(*movie.getDateAdded())),
		QString::fromStdString(std::to_string(std::move(*movie.getReleaseYear()))),
		QString::fromStdString(std::move(*movie.getRating())),
		QString::fromStdString(std::move(*movie.getDuration())),
		QString::fromStdString(std::move(*movie.getListedIn())),
		QString::fromStdString(std::move(*movie.getDescription())),
	};

	return movieInfo;
}
