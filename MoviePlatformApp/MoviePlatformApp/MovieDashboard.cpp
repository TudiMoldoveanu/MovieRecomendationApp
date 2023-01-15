#include "MovieDashboard.h"
#include "ImageTextDelegate.h"

Ui::MovieDashboardClass MovieDashboard::uiDashboard;

MovieDashboard::MovieDashboard(QWidget* parent)
	: QMainWindow(parent)
{
	uiDashboard.setupUi(this);
	uiDashboard.loaderLabel->setVisible(false);
	uiDashboard.pageLoaderLabel->setVisible(false);
	m_randomNumber = randomIndex();
	m_movieIndex = k_paginateNr + m_randomNumber;
	m_allMovies = database->getAll<Movie>();
	m_myProfileData = new QStandardItemModel();
	m_recommendTableData = new QStandardItemModel();
	//signal for displaying individual movie page on double click
	connect(uiDashboard.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(dashboardMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	connect(uiDashboard.wishlistTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(wishlistMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	connect(uiDashboard.watchedTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(watchedMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	connect(uiDashboard.recommendTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(recommendedMovieDoubleClick(const QModelIndex&)), Qt::QueuedConnection);
	//check if user clicked at a tab
	connect(uiDashboard.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
	setMovieDashboardData(m_randomNumber, m_randomNumber + k_paginateNr);
	setMovieWishlistData();
	setMovieWatchedData();
	setRecommendedMoviesData();
	setMyProfileData();
}

MovieDashboard::~MovieDashboard()
{}


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
	m_wishlistTableData = setModelData<UserWishlist>(m_wishlistTableData);
	assignDataToTable(uiDashboard.wishlistTable, m_wishlistTableData);
}

void MovieDashboard::setMovieWatchedData()
{
	m_watchedTableData = setModelData<UserWatched>(m_watchedTableData);
	assignDataToTable(uiDashboard.watchedTable, m_watchedTableData);
}

double jaccardSimilarity(const std::string& s1, const std::string& s2) {
	std::set<std::string> set1, set2;
	std::stringstream s1s(s1), s2s(s2);
	std::string temp;
	while (s1s >> temp) set1.insert(temp);
	while (s2s >> temp) set2.insert(temp);
	std::vector<std::string> intersection;
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
		std::back_inserter(intersection));
	int size = intersection.size();
	return (double)size / (set1.size() + set2.size() - size);
}

void MovieDashboard::setRecommendedMoviesData()
{
	std::vector<int> wishlistedMovieIds = database->getSavedMovies<UserWishlist>(loggedUser->getId());
	std::vector<int> watchedMovieIds = database->getSavedMovies<UserWatched>(loggedUser->getId());

	if (wishlistedMovieIds.size() + watchedMovieIds.size() == 0)
		return;
	
	//create an instance of Recommendation Engine
	RecomendationEngine recEngine(watchedMovieIds, wishlistedMovieIds);
	recEngine.setMovieGenresMap();
	m_recommendedMoviesIds = recEngine.getSimilarMovies();
	
	int count = 0;
	for (const auto& recommendedMovieId : m_recommendedMoviesIds) {
		QPixmap moviePoster = posterManager.getMoviePoster(recommendedMovieId, "154");
		QList<QString> movieInfo = infoManager.getMovieInfo(recommendedMovieId);

		QStandardItem* item = new QStandardItem;
		item->setData(moviePoster, Qt::DisplayRole);
		item->setData(movieInfo[1], Qt::UserRole);
		m_recommendTableData->setItem(0, count, item);
		count++;
	}

	assignDataToTable(uiDashboard.recommendTable, m_recommendTableData);
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
	tableUi->setItemDelegate(new ImageTextDelegate(tableUi));
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

	setMovieView(selectedMovieId);

	uiDashboard.tableView->setEnabled(true);
}

void MovieDashboard::wishlistMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.wishlistTable->setEnabled(false);
	uiDashboard.watchedTable->setEnabled(false);
	std::vector<int> wishlistedMovieIds =
		database->getSavedMovies<UserWishlist>(loggedUser->getId());
	
	int selectedMovieId = wishlistedMovieIds[index.column()];

	setMovieView(selectedMovieId);

	uiDashboard.wishlistTable->setEnabled(true);
	uiDashboard.watchedTable->setEnabled(true);
}

void MovieDashboard::recommendedMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.recommendTable->setEnabled(false);

	int selectedMovieId =  *std::next(m_recommendedMoviesIds.begin(), index.column());

	setMovieView(selectedMovieId);

	uiDashboard.recommendTable->setEnabled(true);
}

void MovieDashboard::watchedMovieDoubleClick(const QModelIndex& index)
{
	uiDashboard.watchedTable->setEnabled(false);
	uiDashboard.wishlistTable->setEnabled(false);
	std::vector<int> watchedMovieIds =
		database->getSavedMovies<UserWatched>(loggedUser->getId());

	int selectedMovieId = watchedMovieIds[index.column()];

	setMovieView(selectedMovieId);

	uiDashboard.watchedTable->setEnabled(true);
	uiDashboard.wishlistTable->setEnabled(true);
}

void MovieDashboard::tabSelected()
{

	/*if (uiDashboard.tabWidget->currentIndex() == 2) {
		setRecommendedMoviesData();
	}*/ // idk if to set it here or at movieView buttons actions
}

void MovieDashboard::on_nextPage_clicked()
{
	uiDashboard.nextPage->setEnabled(false);
	uiDashboard.nextPage->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
	uiDashboard.previousPage->setEnabled(false);
	uiDashboard.previousPage->setStyleSheet("background-color: rgba(255, 255, 255, 50);");

	QMovie* loaderMovie = new QMovie("smallLoader.gif");
	uiDashboard.pageLoaderLabel->setMovie(loaderMovie);
	uiDashboard.pageLoaderLabel->show();
	loaderMovie->start();

	k_currentPage++;
	k_rows = 0;
	m_searchMovies.clear();
	setMovieDashboardData(m_movieIndex, m_movieIndex + k_paginateNr);
	m_movieIndex += k_paginateNr;

	uiDashboard.nextPage->setEnabled(true);
	uiDashboard.nextPage->setStyleSheet(QString::fromUtf8("QPushButton\n"
		"{\n"
		"border-radius:10px;\n"
		"}"));
	uiDashboard.previousPage->setEnabled(true);
	uiDashboard.previousPage->setStyleSheet(QString::fromUtf8("QPushButton\n"
		"{\n"
		"border-radius:10px;\n"
		"}"));

	// stop loading
	uiDashboard.pageLoaderLabel->setVisible(false);
	loaderMovie->stop();
}

void MovieDashboard::on_previousPage_clicked()
{
	if (m_movieIndex < k_paginateNr)
	{
		uiDashboard.previousPage->setEnabled(false);
		uiDashboard.previousPage->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
		return;
	}

	uiDashboard.previousPage->setEnabled(false);
	uiDashboard.previousPage->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
	uiDashboard.nextPage->setEnabled(false);
	uiDashboard.nextPage->setStyleSheet("background-color: rgba(255, 255, 255, 50);");

	QMovie* loaderMovie = new QMovie("smallLoader.gif");
	uiDashboard.pageLoaderLabel->setMovie(loaderMovie);
	uiDashboard.pageLoaderLabel->show();
	loaderMovie->start();

	k_currentPage--;
	k_rows = 0;
	m_searchMovies.clear();
	m_movieIndex -= k_paginateNr;
	setMovieDashboardData(m_movieIndex - k_paginateNr, m_movieIndex);

	uiDashboard.previousPage->setEnabled(true);
	uiDashboard.previousPage->setStyleSheet(QString::fromUtf8("QPushButton\n"
		"{\n"
		"border-radius:10px;\n"
		"}"));
	uiDashboard.nextPage->setEnabled(true);
	uiDashboard.nextPage->setStyleSheet(QString::fromUtf8("QPushButton\n"
		"{\n"
		"border-radius:10px;\n"
		"}"));

	// stop loading
	uiDashboard.pageLoaderLabel->setVisible(false);
	loaderMovie->stop();
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
	uiDashboard.searchButton->setEnabled(false);
	uiDashboard.searchButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");

	std::string searchTitle = uiDashboard.searchBox->text().toStdString();

	if (searchTitle.size() <= 1)
	{
		uiDashboard.searchButton->setEnabled(true);
		uiDashboard.searchButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
			"{\n"
			"border-radius:10px;\n"
			"}"));
		return;
	}

	QMovie* loaderMovie = new QMovie("smallLoader.gif");
	uiDashboard.loaderLabel->setMovie(loaderMovie);
	uiDashboard.loaderLabel->show();
	loaderMovie->start();

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
	// stop loading
	uiDashboard.loaderLabel->setVisible(false);
	loaderMovie->stop();
	// reset the button afterwards
	uiDashboard.searchButton->setEnabled(true);
	uiDashboard.searchButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
		"{\n"
		"border-radius:10px;\n"
		"}"));
}

int MovieDashboard::randomIndex()
{
	srand(time(0));
	return rand() % k_noOfMovies;
}

void MovieDashboard::setMovieView(const int& selectedMovieId) {
	MovieView* movieView = new MovieView(selectedMovieId, this);
	Movie movie = database->getById<Movie>(selectedMovieId);

	QList<QString> movieInfo = infoManager.getMovieInfo(selectedMovieId);
	QPixmap moviePoster = posterManager.getMoviePoster(selectedMovieId, "200");

	movieView->setMovieView();
	movieView->setVisible(true);
}