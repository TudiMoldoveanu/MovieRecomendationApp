#include "MovieDashboard.h"
#include "ImageTextDelegate.h"

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
	m_randomNumber = randomIndex();
	setMovieDashboardData(m_randomNumber, m_randomNumber + k_paginateNr);
	setMovieWishlistData();
	setMovieWatchedData();
	setMyProfileData();
}

MovieDashboard::~MovieDashboard()
{}

void MovieDashboard::setHeader(QStandardItemModel* tableHeader) {
	QList<QString> header = {
		"",
		"Type",
		"Title",
		"Director",
		"Cast",
		"Country",
		"Date Added",
		"Release Year",
		"Rating",
		"Duration",
		"Listed In",
		"Description"
	};
	tableHeader->setHorizontalHeaderLabels(header);
}

void MovieDashboard::setMovieDashboardData(const int& fromId, const int& toId)
{
	m_dashboardTableData = new QStandardItemModel();

	for (int i = fromId; i < toId; i++) {
		setMovieData(i - fromId, i + 1, m_dashboardTableData);
	}

	assignDataToTable(uiDashboard.tableView, m_dashboardTableData);
}

void MovieDashboard::setMovieWishlistData()
{
	std::vector<int> wishlistedMovieIds =
		database->getSavedMovies<UserWishlist>(loggedUser->getId());

	for (int i = 0; i < wishlistedMovieIds.size(); i++) {
		QPixmap moviePoster = posterManager.getMoviePoster(wishlistedMovieIds[i], "154");
		QList<QString> movieInfo = infoManager.getMovieInfo(wishlistedMovieIds[i]);

		uiDashboard.wishlistTable->setItemDelegate(new ImageTextDelegate(uiDashboard.wishlistTable));
		
		QStandardItem* item = new QStandardItem;
		item->setData(moviePoster, Qt::DisplayRole);
		item->setData(movieInfo[1], Qt::UserRole);
		m_wishlistTableData->setItem(0, i, item);
	}

	assignDataToTable(uiDashboard.wishlistTable, m_wishlistTableData);
}

void MovieDashboard::setMovieWatchedData()
{
	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	for (int i = 0; i < watchedMovieIds.size(); i++) {
		QPixmap moviePoster = posterManager.getMoviePoster(watchedMovieIds[i], "154");
		QList<QString> movieInfo = infoManager.getMovieInfo(watchedMovieIds[i]);

		uiDashboard.watchedTable->setItemDelegate(new ImageTextDelegate(uiDashboard.watchedTable));

		QStandardItem* item = new QStandardItem;
		item->setData(moviePoster, Qt::DisplayRole);
		item->setData(movieInfo[1], Qt::UserRole);
		m_watchedTableData->setItem(0, i, item);
	}

	assignDataToTable(uiDashboard.watchedTable, m_watchedTableData);
}

void MovieDashboard::setRecommendedMoviesData()
{
	std::vector<int> wishlistedMovieIds = database->getSavedMovies<UserWishlist>(loggedUser->getId());
	std::vector<int> watchedMovieIds = database->getSavedMovies<UserWatched>(loggedUser->getId());
	//create an instance of Recommendation Engine
	RecomendationEngine recEngine(watchedMovieIds, wishlistedMovieIds);
	recEngine.setMovieGenresMap();
	std::vector<int> recommendedMoviesIds = recEngine.getSimilarMovies();
	
	for (int i = 0; i < recommendedMoviesIds.size(); i++)
	{
		std::cout << recommendedMoviesIds[i] << " ";
	}

}

void MovieDashboard::setMyProfileData()
{
	auto userName = database->getById<UserInfo>(loggedUser->getId()).getFullName();
	QString qstrUserName = QString::fromStdString(userName);
	uiDashboard.yourNameLabel->setText(qstrUserName + "!");
}

void MovieDashboard::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
	QStandardItem* movieData = new QStandardItem;

	QPixmap moviePoster = posterManager.getMoviePoster(movieId, "154");
	QList<QString> movieInfo = infoManager.getMovieInfo(movieId);

	uiDashboard.tableView->setItemDelegate(new ImageTextDelegate(uiDashboard.tableView));

	movieData->setData(moviePoster, Qt::DisplayRole);
	movieData->setData(movieInfo[1], Qt::UserRole);

	if ((tableLine + 1) % k_cols) {
		tableData->setItem(k_rows, tableLine - k_rows * k_cols, movieData);
	}
	else {
		tableData->setItem(k_rows, tableLine - k_rows * k_cols, movieData);
		k_rows++;
	}
}

void MovieDashboard::assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData) {

	//set data
	tableUi->setModel(tableData);
	//set styling
	tableUi->setCursor(Qt::PointingHandCursor);
	tableUi->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableUi->setSelectionBehavior(QAbstractItemView::SelectItems);
	tableUi->verticalHeader()->setDefaultSectionSize(260);
	tableUi->horizontalHeader()->setDefaultSectionSize(165);
	tableUi->setFrameStyle(QFrame::NoFrame);
	tableUi->horizontalHeader()->hide();
	tableUi->verticalHeader()->hide();
	tableUi->setFocusPolicy(Qt::NoFocus);
	tableUi->setSelectionMode(QAbstractItemView::NoSelection);
	tableUi->setShowGrid(false);
	tableUi->setStyleSheet
	(
		"QHeaderView::section { background-color:#073d69}\n"
		"QTableView QTableCornerButton::section { background-color:#073d69}"
	);
	tableUi->show();
}

void MovieDashboard::dashboardMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.tableView->setEnabled(false);
	QModelIndexList selection = uiDashboard.tableView->selectionModel()->selectedIndexes();
	int selectedMovieId;

	if (!m_searchMovies.empty()) {
		selectedMovieId = m_searchMovies[index.column()];
	}
	else {
		selectedMovieId = (k_currentPage * k_paginateNr) + index.row() * k_cols + index.column() + m_randomNumber + 1;
	}

	MovieView* movieView = new MovieView(selectedMovieId, this);
	movieView->setMovieView();
	movieView->setVisible(true);
	uiDashboard.tableView->setEnabled(true);
}

void MovieDashboard::wishlistMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.wishlistTable->setEnabled(false);
	uiDashboard.watchedTable->setEnabled(false);
	std::vector<int> wishlistedMovieIds =
		database->getSavedMovies<UserWishlist>(loggedUser->getId());
	
	int selectedMovieId = wishlistedMovieIds[index.column()];

	MovieView* movieView = new MovieView(selectedMovieId, this);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = infoManager.getMovieInfo(selectedMovieId);
	QPixmap moviePoster = posterManager.getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView();
	movieView->setVisible(true);
	uiDashboard.wishlistTable->setEnabled(true);
	uiDashboard.watchedTable->setEnabled(true);
}

void MovieDashboard::watchedMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.watchedTable->setEnabled(false);
	uiDashboard.wishlistTable->setEnabled(false);
	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	int selectedMovieId = watchedMovieIds[index.column()];

	MovieView* movieView = new MovieView(selectedMovieId, this);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = infoManager.getMovieInfo(selectedMovieId);
	QPixmap moviePoster = posterManager.getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView();
	movieView->setVisible(true);
	uiDashboard.watchedTable->setEnabled(true);
	uiDashboard.wishlistTable->setEnabled(true);
}

void MovieDashboard::tabSelected()
{
	//if My Profile is selected
	if (uiDashboard.tabWidget->currentIndex() == 0) {
		setMovieWishlistData();
		setMovieWatchedData();
	}
	if (uiDashboard.tabWidget->currentIndex() == 2) {
		setRecommendedMoviesData();
	}

}

void MovieDashboard::on_nextPage_clicked()
{
	k_currentPage++;
	k_rows = 0;
	m_searchMovies.clear();
	setMovieDashboardData(m_movieIndex, m_movieIndex + k_paginateNr);
	m_movieIndex += k_paginateNr;
}

void MovieDashboard::on_previousPage_clicked()
{
	k_currentPage--;
	k_rows = 0;
	m_searchMovies.clear();
	m_movieIndex -= k_paginateNr;
	setMovieDashboardData(m_movieIndex - k_paginateNr, m_movieIndex);
}

void MovieDashboard::on_settingsButton_clicked()
{
	uiDashboard.settingsButton->setDisabled(true);
	SettingsPage* settingsPage = new SettingsPage(this);
	settingsPage->setVisible(true);
	uiDashboard.settingsButton->setDisabled(false);

}

void MovieDashboard::on_searchButton_clicked()
{
	std::string searchTitle = uiDashboard.searchBox->text().toStdString();
	std::ranges::transform(searchTitle, searchTitle.begin(), ::toupper);
	int nrOfMoviesFound = 0;

	m_dashboardTableData = new QStandardItemModel();
	m_searchMovies.clear();

	k_rows = 0;
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

	assignDataToTable(uiDashboard.tableView, m_dashboardTableData);
}

int MovieDashboard::randomIndex()
{
	srand(time(0));
	return rand() % k_noOfMovies;
}