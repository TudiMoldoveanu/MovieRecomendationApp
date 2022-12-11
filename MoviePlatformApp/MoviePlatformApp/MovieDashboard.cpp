#include "MovieDashboard.h"

const int PAGINATE_NR = 5;

MovieDashboard::MovieDashboard(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_movieIndex = PAGINATE_NR;
	m_allMovies = database->getAll<Movie>();
	m_dashboardTableData = new QStandardItemModel();
	m_wishlistTableData = new QStandardItemModel();
	m_watchedTableData = new QStandardItemModel();
	//signal for displaying individual movie page on double click
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	//check if user clicked at a tab
	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
	setMovieDashboardData(0, PAGINATE_NR);
	setMovieWishlistData();
	setMovieWatchedData();
}

MovieDashboard::~MovieDashboard()
{}

void MovieDashboard::setHeader(QStandardItemModel* tableHeader) {
	QList<QString> header = { "", "Type", "Title", "Director", "Cast", "Country", "Date Added", "Release Year", "Rating", "Duration", "Listed In", "Description" };
	tableHeader->setHorizontalHeaderLabels(header);
}

void MovieDashboard::setMovieDashboardData(const int& fromId, const int& toId)
{
	setHeader(m_dashboardTableData);

	for (int i = fromId; i < toId; i++) {
		setMovieData(i, i + 1, m_dashboardTableData);
	}

	assignDataToTable(ui.tableView, m_dashboardTableData);
}

void MovieDashboard::setMovieWishlistData()
{
	setHeader(m_watchedTableData);

	std::vector<int> wishlistedMovieIds = 
		database->getSavedMovies<UserWishlist>(loggedUser->getId());

	for (int i = 0; i < wishlistedMovieIds.size(); i++) {
		setMovieData(i, wishlistedMovieIds[i], m_wishlistTableData);
	}

	assignDataToTable(ui.tableView_2, m_wishlistTableData);
}

void MovieDashboard::setMovieWatchedData()
{
	setHeader(m_wishlistTableData);

	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	for (int i = 0; i < watchedMovieIds.size(); i++) {
		setMovieData(i, watchedMovieIds[i], m_watchedTableData);
	}

	assignDataToTable(ui.tableView_3, m_watchedTableData);
}

QList<QString> MovieDashboard::getMovieInfo(const int& id) {

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

void MovieDashboard::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
	QStandardItem* movieData = new QStandardItem();

	QPixmap moviePoster = getMoviePoster(movieId, "92");
	QList<QString> movieInfo = getMovieInfo(movieId);

	movieData->setData(QVariant(moviePoster), Qt::DecorationRole);
	tableData->setItem(tableLine, 0, movieData);
	for (int col = 1; col < 12; col++) {
		movieData = new QStandardItem(movieInfo[col - 1]);
		tableData->setItem(tableLine, col, movieData);
	}
}

void MovieDashboard::assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData) {

	//set data
	tableUi->setModel(tableData);
	//set styling
	tableUi->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableUi->setSelectionMode(QAbstractItemView::SingleSelection);
	tableUi->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableUi->verticalHeader()->setDefaultSectionSize(140);
	tableUi->horizontalHeader()->setDefaultSectionSize(92);
	tableUi->setStyleSheet
	(
		"QHeaderView::section { background-color:#073d69}\n"
		"QTableView QTableCornerButton::section { background-color:#073d69}"
	);
	tableUi->show();
}

void MovieDashboard::onMovieDoubleClick(const QModelIndex& index)
{
	QModelIndexList indexes = ui.tableView->selectionModel()->selection().indexes();
	int selectedMovieId = (indexes.at(0).row() + 1);

	MovieView* movieView = new MovieView(selectedMovieId);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = getMovieInfo(selectedMovieId);
	QPixmap moviePoster = getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView(movieInfo, moviePoster);
	movieView->setVisible(true);
}

void MovieDashboard::tabSelected()
{
	//if wishlist selected
	if (ui.tabWidget->currentIndex() == 1) {
		setMovieWishlistData();
	}
	//if watched selected
	else if (ui.tabWidget->currentIndex() == 2) {
		setMovieWatchedData();
	}
}

std::string MovieDashboard::whiteSpaceReplace(std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (isspace((unsigned char)s[i]))
			s[i] = '+';
	return s;
}

QPixmap MovieDashboard::getMoviePoster(const int& id, const std::string& size) {

	Movie movie = database->getById<Movie>(id);

	std::string moviePosterUrl = std::move(*movie.getPosterUrl());
	std::string movieTitle = std::move(*movie.getPosterUrl());

	QUrl requestUrl;
	if (moviePosterUrl.empty()) {
		whiteSpaceReplace(movieTitle);
		QString finalUrl = "https://placehold.co/" + QString::fromStdString(size) + "x500/black/white";
		requestUrl = QUrl(finalUrl);
	}
	else {
		QString finalUrl = "https://image.tmdb.org/t/p/w" + QString::fromStdString(size) + QString::fromStdString(moviePosterUrl);
		requestUrl = QUrl(finalUrl);
	}

	return downloadMoviePoster(requestUrl);
}

QPixmap MovieDashboard::downloadMoviePoster(QUrl url) {

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

void MovieDashboard::on_loadMore_clicked()
{
	setMovieDashboardData(m_movieIndex, m_movieIndex + PAGINATE_NR);
	m_movieIndex += PAGINATE_NR;
}

void MovieDashboard::on_searchButton_clicked() { //search method to be improved

	std::string searchTitle = ui.searchBox->text().toStdString();
	int nrOfMoviesFound = 0;

	m_dashboardTableData = new QStandardItemModel();

	for (const auto& movie : m_allMovies) {
		std::string movieTitle = std::move(*movie.getTitle());
		if (movieTitle.find(searchTitle) != std::string::npos) {
			int id = movie.getId();
			setMovieData(nrOfMoviesFound, id, m_dashboardTableData);
			nrOfMoviesFound++;
		}
	}

	assignDataToTable(ui.tableView, m_dashboardTableData);
}