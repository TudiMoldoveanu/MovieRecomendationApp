#include "MovieDashboard.h"

Ui::MovieDashboardClass MovieDashboard::uiDashboard;

MovieDashboard::MovieDashboard(QWidget* parent)
	: QMainWindow(parent)
{
	uiDashboard.setupUi(this);
	m_movieIndex = k_paginateNr;
	m_allMovies = database->getAll<Movie>();
	m_wishlistTableData = new QStandardItemModel();
	m_watchedTableData = new QStandardItemModel();
	m_myProfileData = new QStandardItemModel();
	//signal for displaying individual movie page on double click
	connect(uiDashboard.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(dashboardMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	connect(uiDashboard.wishlistTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(wishlistMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	connect(uiDashboard.watchedTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(watchedMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	//check if user clicked at a tab
	connect(uiDashboard.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
	setMovieDashboardData(0, k_paginateNr);
	setMovieWishlistData();
	setMovieWatchedData();
	setMyProfileData();
}

MovieDashboard::~MovieDashboard()
{}

void MovieDashboard::setHeader(QStandardItemModel* tableHeader) {
	QList<QString> header = { "", "Type", "Title", "Director", "Cast", "Country", "Date Added", "Release Year", "Rating", "Duration", "Listed In", "Description" };
	tableHeader->setHorizontalHeaderLabels(header);
}

void MovieDashboard::setMovieDashboardData(const int& fromId, const int& toId)
{
	m_dashboardTableData = new QStandardItemModel();
	setHeader(m_dashboardTableData);

	srand(time(0));

	for (int i = fromId; i < toId; i++) {
		setMovieData(i-fromId, i + 1, m_dashboardTableData);
	}

	assignDataToTable(uiDashboard.tableView, m_dashboardTableData);
}

void MovieDashboard::setMovieWishlistData()
{
	setHeader(m_wishlistTableData);

	std::vector<int> wishlistedMovieIds = 
		database->getSavedMovies<UserWishlist>(loggedUser->getId());

	for (int i = 0; i < wishlistedMovieIds.size(); i++) {
		setMovieData(i, wishlistedMovieIds[i], m_wishlistTableData);
	}

	assignDataToTable(uiDashboard.wishlistTable, m_wishlistTableData);
}

void MovieDashboard::setMovieWatchedData()
{
	setHeader(m_watchedTableData);

	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	for (int i = 0; i < watchedMovieIds.size(); i++) {
		setMovieData(i, watchedMovieIds[i], m_watchedTableData);
	}

	assignDataToTable(uiDashboard.watchedTable, m_watchedTableData);
}

void MovieDashboard::setMyProfileData()
{
	auto userName = database->getById<UserInfo>(loggedUser->getId()).getFullName();
	QString qstrUserName = QString::fromStdString(userName);
	uiDashboard.yourNameLabel ->setText(qstrUserName + "!");
}

void MovieDashboard::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
	QStandardItem* movieData = new QStandardItem();

	QPixmap moviePoster = posterManager.getMoviePoster(movieId, "92");
	QList<QString> movieInfo = infoManager.getMovieInfo(movieId);

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

void MovieDashboard::dashboardMovieDoubleClick(const QModelIndex& index)
{
	QModelIndexList indexes = uiDashboard.tableView->selectionModel()->selection().indexes();
	int selectedMovieId;
	if (!m_searchMovies.empty()) {
		selectedMovieId = m_searchMovies[indexes.at(0).row()];
	}
	else {
		selectedMovieId = (indexes.at(0).row() + 1) + m_movieIndex - k_paginateNr;
	}

	MovieView* movieView = new MovieView(selectedMovieId, this);

	movieView->setMovieView();
	movieView->setVisible(true);
}

void MovieDashboard::wishlistMovieDoubleClick(const QModelIndex& index)
{
	std::vector<int> wishlistedMovieIds =
		database->getSavedMovies<UserWishlist>(loggedUser->getId());

	QModelIndexList indexes = uiDashboard.wishlistTable->selectionModel()->selection().indexes();
	int selectedMovieId = wishlistedMovieIds[(indexes.at(0).row())];

	MovieView* movieView = new MovieView(selectedMovieId, this);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = infoManager.getMovieInfo(selectedMovieId);
	QPixmap moviePoster = posterManager.getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView();
	movieView->setVisible(true);
}

void MovieDashboard::watchedMovieDoubleClick(const QModelIndex& index)
{
	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	QModelIndexList indexes = uiDashboard.watchedTable->selectionModel()->selection().indexes();
	int selectedMovieId = watchedMovieIds[(indexes.at(0).row())];

	MovieView* movieView = new MovieView(selectedMovieId, this);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = infoManager.getMovieInfo(selectedMovieId);
	QPixmap moviePoster = posterManager.getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView();
	movieView->setVisible(true);
}

void MovieDashboard::tabSelected()
{
	//if My Profile is selected
	if (uiDashboard.tabWidget->currentIndex() == 0) {
		setMovieWishlistData();
		setMovieWatchedData();
	}
	
}

void MovieDashboard::on_nextPage_clicked()
{
	m_searchMovies.clear();
	setMovieDashboardData(m_movieIndex, m_movieIndex + k_paginateNr);
	m_movieIndex += k_paginateNr;
}

void MovieDashboard::on_previousPage_clicked()
{
	m_searchMovies.clear();
	if (m_movieIndex - k_paginateNr >= 5) 
		{
			m_movieIndex -= k_paginateNr;
			setMovieDashboardData(m_movieIndex - k_paginateNr, m_movieIndex);
		}
}

void MovieDashboard::on_settingsButton_clicked()
{
	uiDashboard.settingsButton->setDisabled(true);
	SettingsPage* settingsPage = new SettingsPage(this);
	settingsPage->setVisible(true);
	uiDashboard.settingsButton->setDisabled(false);

}

void MovieDashboard::on_searchButton_clicked() 
{ //search method to be improved
	std::string searchTitle = uiDashboard.searchBox->text().toStdString();
	std::ranges::transform(searchTitle, searchTitle.begin(), ::toupper);
	int nrOfMoviesFound = 0;

	m_dashboardTableData = new QStandardItemModel();
	m_searchMovies.clear();

	for (const auto& movie : m_allMovies) 
	{
		std::string movieTitle = std::move(*movie.getTitle());
		std::transform(movieTitle.begin(), movieTitle.end(), movieTitle.begin(), ::toupper);
		if (movieTitle.find(searchTitle) != std::string::npos) 
			{
				int id = movie.getId();
				m_searchMovies.push_back(id);
				setMovieData(nrOfMoviesFound, id, m_dashboardTableData);
				nrOfMoviesFound++;
			}
	}

	setHeader(m_dashboardTableData);
	assignDataToTable(uiDashboard.tableView, m_dashboardTableData);
}