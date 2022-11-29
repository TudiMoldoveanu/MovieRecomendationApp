#include "MovieDashboard.h"
#include "Movie.h"
#include <QList>

const int PAGINATE_NR = 20;

MovieDashboard::MovieDashboard(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->allMovies = database->getAll<Movie>();

	this->movieIndex = PAGINATE_NR;

	this->model = new QStandardItemModel();

	setHeader();

	loadMovieData(0, PAGINATE_NR, "dashboard");
}

MovieDashboard::~MovieDashboard()
{}

void MovieDashboard::setHeader() {
	//heading title for table
	QList<QString> header = { "Poster Url", "Type", "Title", "Director", "Cast", "Country", "Date Added", "Release Year", "Rating", "Duration", "Listed In", "Description" };
	model->setHorizontalHeaderLabels(header);
}

void MovieDashboard::loadMovieData(int fromIndex, int toIndex, std::string optiune)
{
	model->removeRows(0, 0);

	//add 10 items to the table
	for (int line = fromIndex; line < toIndex; line++) {

		QStandardItem* newItem = new QStandardItem();
	
		//add movie poster
		std::string moviePoster = std::move(*allMovies[line].getPosterUrl());
		std::string movieTitle = std::move(*allMovies[line].getTitle());

		QPixmap pm = downloadFrom(moviePoster, movieTitle);
		newItem->setData(QVariant(pm), Qt::DecorationRole);

		//add rest of the infos
		QList<QString> movie = { 
			QString::fromStdString(std::move(*allMovies[line].getType())),
			QString::fromStdString(movieTitle), 
			QString::fromStdString(std::move(*allMovies[line].getDirector())) ,
			QString::fromStdString(std::move(*allMovies[line].getCast())),
			QString::fromStdString(std::move(*allMovies[line].getCountry())),
			QString::fromStdString(std::move(*allMovies[line].getDateAdded())),
			QString::fromStdString(std::to_string(std::move(*allMovies[line].getReleaseYear()))),
			QString::fromStdString(std::move(*allMovies[line].getRating())),
			QString::fromStdString(std::move(*allMovies[line].getDuration())),
			QString::fromStdString(std::move(*allMovies[line].getListedIn())),
			QString::fromStdString(std::move(*allMovies[line].getDescription())),
		};

		//change - fromIndex (change back to get scroll load)
		if (optiune == "search") {
			this->model = new QStandardItemModel();
			setHeader();
			model->setItem(line - fromIndex, 0, newItem);
			for (int col = 1; col < 12; col++) {
				newItem = new QStandardItem(movie[col - 1]);
				model->setItem(line - fromIndex, col, newItem);
			}
		}
		else if (optiune == "dashboard") {
			model->setItem(line, 0, newItem);
			for (int col = 1; col < 12; col++) {
				newItem = new QStandardItem(movie[col - 1]);
				model->setItem(line, col, newItem);
			}
		}
	}

	//set size for cells
	ui.tableView->verticalHeader()->setDefaultSectionSize(140);
	ui.tableView->horizontalHeader()->setDefaultSectionSize(92);
	ui.tableView->setModel(model);
	ui.tableView->show();
}

std::string MovieDashboard::whitespaceReplace(std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (isspace((unsigned char)s[i]))
			s[i] = '+';
	return s;
}

QPixmap MovieDashboard::downloadFrom(const std::string& poster_url, const std::string& title) {

	//check is poster is null
	QUrl url;
	if (poster_url.empty()) {
		//replace whitespace with "+" to use for placholder link
		std::string title_copy = title;
		whitespaceReplace(title_copy);

		std::string URL_STRING = "https://placehold.co/92x500?text=" + title_copy;
		const char* URL_CHAR = URL_STRING.c_str();
		url = QUrl(URL_CHAR);
	}
	else {
		//concatenate url from database
		std::string URL_STRING = "https://image.tmdb.org/t/p/w92" + poster_url;
		const char* URL_CHAR = URL_STRING.c_str();
		url = QUrl(URL_CHAR);
	}

	//make request to network
	QNetworkAccessManager nam;
	QEventLoop loop;
	ui.loadMoreButton->setText("Loading...");
	ui.loadMoreButton->setEnabled(false);
	QObject::connect(&nam, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
	QNetworkReply* reply = nam.get(QNetworkRequest(url));
	loop.exec();
	ui.loadMoreButton->setEnabled(true);
	ui.loadMoreButton->setText("Load 20 More");

	QPixmap pm;
	pm.loadFromData(reply->readAll());

	delete reply;
	return pm;
}

void MovieDashboard::on_loadMoreButton_clicked()
{
	loadMovieData(movieIndex, movieIndex + PAGINATE_NR, "dashboard");
	movieIndex += PAGINATE_NR;
}

void MovieDashboard::on_searchButton_clicked() { //search method to be improved
	std::string i_movieTitle = ui.searchBox->text().toStdString();

	for (const auto& movie : allMovies) {
		//set text to searching
		std::string movieTitle = std::move(*movie.getTitle());
		if (movieTitle.find(i_movieTitle) != std::string::npos) {
			int id = movie.getId();
			//std::cout << movieTitle << std::endl;
			loadMovieData(id-1, id, "search");
		}
	}
}