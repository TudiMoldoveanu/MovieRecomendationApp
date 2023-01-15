#pragma once
#include "Database.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QApplication>

class PosterManager
{
private:
	Database* database = Database::connect();
public:
	PosterManager();

	std::string whiteSpaceReplace(std::string& s);
	QPixmap getMoviePoster(const int& id, const std::string& width);
	QPixmap downloadMoviePoster(const QUrl& url);
};

