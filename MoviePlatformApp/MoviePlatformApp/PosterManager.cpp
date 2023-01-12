#include "PosterManager.h"

PosterManager::PosterManager()
{}

std::string PosterManager::whiteSpaceReplace(std::string & s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (isspace((unsigned char)s[i]))
			s[i] = '+';
	return s;
}

QPixmap PosterManager::getMoviePoster(const int& id, const std::string& size)
{
	Movie movie = database->getById<Movie>(id);

	std::string moviePosterUrl = std::move(*movie.getPosterUrl());
	std::string movieTitle = std::move(*movie.getTitle());

	QUrl requestUrl;
	if (moviePosterUrl.empty()) {
		whiteSpaceReplace(movieTitle);
		QString finalUrl = "https://placehold.co/" + QString::fromStdString(size) + "x500?text=" + QString::fromStdString(whiteSpaceReplace(movieTitle));
		requestUrl = QUrl(finalUrl);
	}
	else {
		QString finalUrl = "https://image.tmdb.org/t/p/w" + QString::fromStdString(size) + QString::fromStdString(moviePosterUrl);
		requestUrl = QUrl(finalUrl);
	}

	return downloadMoviePoster(requestUrl);
}

QPixmap PosterManager::downloadMoviePoster(const QUrl& url)
{
	QNetworkAccessManager network;
	QEventLoop loop;
	QObject::connect(&network, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
	QNetworkReply* reply = network.get(QNetworkRequest(url));
	loop.exec();

	QPixmap moviePoster;
	moviePoster.loadFromData(reply->readAll());

	delete reply;
	return moviePoster;
}
