#include "MovieDashboard.h"
#include "Movie.h"
#include <QStandardItemModel>
#include <QList>

MovieDashboard::MovieDashboard(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	loadMovieData();
}

MovieDashboard::~MovieDashboard()
{}

void MovieDashboard::loadMovieData()
{

	auto allMovies = database->getAll<Movie>();
	QStandardItemModel* model = new QStandardItemModel();

	//heading title for table
	QList<QString> header = {"Poster Url", "Type", "Title", "Director", "Cast", "Country", "Date Added", "Release Year", "Rating", "Duration", "Listed In", "Description"};
	model->setHorizontalHeaderLabels(header);

	//add first 60 items to table
	for (int line = 0; line < 60; line++) {

		QStandardItem* newItem = new QStandardItem();
	
		//add movie poster
		QPixmap pm = download_from(std::move(*allMovies[line].getPosterUrl()));
		newItem->setData(QVariant(pm), Qt::DecorationRole);
		model->setItem(line, 0, newItem); 

		//add rest of the infos
		auto title = std::move(*allMovies[line].getTitle());
		auto type = std::move(*allMovies[line].getType());
		auto director = std::move(*allMovies[line].getDirector());
		auto cast = std::move(*allMovies[line].getCast());
		auto country = std::move(*allMovies[line].getCountry());
		auto date_added = std::move(*allMovies[line].getDateAdded());
		auto release_year = std::move(*allMovies[line].getReleaseYear());
		auto rating = std::move(*allMovies[line].getRating());
		auto duration = std::move(*allMovies[line].getDuration());
		auto listed_in = std::move(*allMovies[line].getListedIn());
		auto description = std::move(*allMovies[line].getDescription());

		QList<QString> movie = { 
			QString::fromStdString(type), 
			QString::fromStdString(title), 
			QString::fromStdString(director) ,
			QString::fromStdString(cast),
			QString::fromStdString(country),
			QString::fromStdString(date_added),
			QString::fromStdString(std::to_string(release_year)),
			QString::fromStdString(rating),
			QString::fromStdString(duration),
			QString::fromStdString(listed_in),
			QString::fromStdString(description),
		};

		for (int col = 1; col < 12; col++) {
			newItem = new QStandardItem(movie[col-1]);
			model->setItem(line, col, newItem);
		}
	}

	//set size for cells
	ui.tableView->verticalHeader()->setDefaultSectionSize(140);
	ui.tableView->horizontalHeader()->setDefaultSectionSize(92);
	ui.tableView->setModel(model);
	ui.tableView->show();
}

QPixmap MovieDashboard::download_from(const std::string& poster_url) {

	//concatenate url from database
	std::string URL_STRING = "https://image.tmdb.org/t/p/w92" + poster_url;
	const char* URL_CHAR = URL_STRING.c_str();
	QUrl url = QUrl(URL_CHAR);

	//make request to network
	QNetworkAccessManager nam;
	QEventLoop loop;
	QObject::connect(&nam, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
	QNetworkReply* reply = nam.get(QNetworkRequest(url));
	loop.exec();

	QPixmap pm;
	pm.loadFromData(reply->readAll());

	delete reply;
	return pm;
}