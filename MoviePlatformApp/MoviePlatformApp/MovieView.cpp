#include "MovieView.h"
#include "stardelegate.h"
#include "starrating.h"
#include <QTableWidget>

MovieView::MovieView(int selectedMovieId, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    connect(ui.similarMoviesTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(similarTableDoubleClick(const QModelIndex&)), Qt::QueuedConnection);

    m_selectedMovieId = selectedMovieId;

    m_similarMovieTable = new QStandardItemModel;
    m_parent = parent;
}

MovieView::~MovieView()
{}

void MovieView::setMovieView() {
    Movie movie = database->getById<Movie>(m_selectedMovieId);

    //created an instance of SimilarMoviesEngine
    SimilarMoviesEngine similarMovies(movie);
    m_similarMovieIds = similarMovies.getMoviesId();

    //set data
    m_similarMovieTable = new QStandardItemModel();

    for (int i = 0; i < m_similarMovieIds.size(); i++) {
        setMovieData(i, m_similarMovieIds[i], m_similarMovieTable);
    }

    assignDataToTable(ui.similarMoviesTable, m_similarMovieTable);
    //
   

    QList<QString> movieInfo = infoManager.getMovieInfo(m_selectedMovieId);
    QPixmap moviePoster = posterManager.getMoviePoster(m_selectedMovieId, "200");

    setMovieRating();
    setMoviePoster(moviePoster);
    setMovieTitle(movieInfo[1]);
    setMovieDirector(movieInfo[2]);
    setMovieCast(movieInfo[3]);
    setMovieCountry(movieInfo[4]);
    setMovieReleaseYear(movieInfo[6]);
    setMovieDescription(movieInfo[10]);
    setMovieListedIn(movieInfo[9]);
    setMovieTypeAndDuration(movieInfo[0], movieInfo[8]);
    std::vector<int> wishlistedMovieIds = database->getSavedMovies<UserWishlist>(loggedUser->getId());
    std::vector<int> watchedMovieIds = database->getSavedMovies<UserWatched>(loggedUser->getId());
    for (int i = 0; i < wishlistedMovieIds.size(); i++) 
    {
        if (m_selectedMovieId == wishlistedMovieIds[i])
        {
            ui.wishlistButton->setText("Remove Wishlist");
            ui.wishlistButton->setStyleSheet("background-color: rgb(139,0,0)");
            break;
        }
        else {
            ui.wishlistButton->setText("Add to Wishlist");
            ui.wishlistButton->setStyleSheet("background-color: #e8a813;");
        }
    }
    for (int i = 0; i < watchedMovieIds.size(); i++) {
        if (m_selectedMovieId == watchedMovieIds[i]) {
            ui.watchedButton->setText("Remove Watched");
            ui.watchedButton->setStyleSheet("background-color: rgb(139,0,0)");
            break;
        } else {
            ui.watchedButton->setText("Mark as Watched");
            ui.watchedButton->setStyleSheet("background-color: #e8a813;");
        }
    }
}

void MovieView::setMoviePoster(QPixmap image)
{
	ui.posterImage->setPixmap(image);
}

void MovieView::setMovieTitle(QString title)
{
	ui.movieTitle->setText(title);
}

void MovieView::setMovieRating()
{
     int k_starsRated = 5;
     if (database->userAlreadyRated(loggedUser->getId(), m_selectedMovieId))
     {
         try {
             k_starsRated = database->getById<Rating>(loggedUser->getId(), m_selectedMovieId).getRating();
         }

         catch (std::system_error& e)
         {
             // do nothing
         }
     }


     struct {
        int rating;
    } Data[] = {
        { k_starsRated }
    };

    ui.tableWidget->setColumnCount(1);
    ui.tableWidget->setRowCount(1);
    ui.tableWidget->setItemDelegate(new StarDelegate(m_selectedMovieId));
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget->horizontalHeader()->hide();
    ui.tableWidget->verticalHeader()->hide();
    ui.tableWidget->setFrameStyle(QFrame::NoFrame);
    ui.tableWidget->setShowGrid(false);
    ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    //populate
    QTableWidgetItem* rating = new QTableWidgetItem;
    rating->setData(0, QVariant::fromValue(StarRating(Data[0].rating)));
    ui.tableWidget->setItem(0, 0, rating);
    ui.tableWidget->resizeColumnsToContents();
    ui.tableWidget->show();
}

void MovieView::setMovieDirector(QString director)
{
    if (director.isEmpty()) {
        ui.movieDirector->setText("Not available");
    }
    else {
        ui.movieDirector->setText(director);
    }
}

void MovieView::setMovieCast(QString cast)
{
    if (cast.isEmpty()) {
        ui.movieCast->setText("Not available");
    }
    else {
        ui.movieCast->setText(cast);
    }
}

void MovieView::setMovieCountry(QString country)
{
    if (country.isEmpty()) {
        ui.movieCountry->setText("Not available");
    }
    else {
        ui.movieCountry->setText(country);
    }
}

void MovieView::setMovieReleaseYear(QString release_year)
{
    if (release_year.isEmpty()) {
        ui.movieReleaseYear->setText("Not available");
    }
    else {
        ui.movieReleaseYear->setText(release_year);
    }
}

void MovieView::setMovieDescription(QString description)
{
    if (description.isEmpty()) {
        ui.movieDescription->setText("Not available");
    }
    else {
        ui.movieDescription->viewport()->setAutoFillBackground(false);
        ui.movieDescription->setFrameStyle(QFrame::NoFrame);
        ui.movieDescription->setText(description);
    }
}

void MovieView::setMovieListedIn(QString listed_in)
{
    if (listed_in.isEmpty()) {
        ui.movieListedIn->setText("Not available");
    }
    else {
        ui.movieListedIn->setText(listed_in);
    }
}

void MovieView::setMovieTypeAndDuration(QString type, QString duration)
{
    if (type.isEmpty()) {
        ui.movieType->setText("Not available");
    }
    else {
        ui.movieType->setText(type + " (" + duration + ")");
    }
}

void MovieView::on_watchedButton_clicked()
{
    int userId = loggedUser->getId();
    if (ui.watchedButton->text().toStdString() == "Remove Watched") {
        database->deleteId<UserWatched>(userId, m_selectedMovieId);
        ui.watchedButton->setText("Mark as Watched");
        ui.watchedButton->setStyleSheet("background-color: #e8a813;");
    }
    else {
        UserWatched userWatched(userId, m_selectedMovieId);
        database->replace(userWatched);
        ui.watchedButton->setText("Remove Watched");
        ui.watchedButton->setStyleSheet("background-color: rgb(139,0,0)");
    }
    MovieDashboard* dashboard = (MovieDashboard*)m_parent;
    dashboard->setMovieWatchedData();
    dashboard->setRecommendedMoviesData(); // i think it's pretty difficult to trigger the algorithms at every button action
}

void MovieView::on_wishlistButton_clicked()
{
    int userId = loggedUser->getId();
    if (ui.wishlistButton->text().toStdString() == "Remove Wishlist") {
        database->deleteId<UserWishlist>(userId, m_selectedMovieId);
        ui.wishlistButton->setText("Add to Wishlist");
        ui.wishlistButton->setStyleSheet("background-color: #e8a813;");
    }
    else {
        UserWishlist userWishlist(userId, m_selectedMovieId);
        database->replace(userWishlist);
        ui.wishlistButton->setText("Remove Wishlist");
        ui.wishlistButton->setStyleSheet("background-color: rgb(139,0,0)");
    }
    MovieDashboard* dashboard = (MovieDashboard*)m_parent;
    dashboard->setMovieWishlistData();
    dashboard->setRecommendedMoviesData(); // same as above
}

void MovieView::assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData) {

    //set data
    tableUi->setModel(tableData);
    //set styling
    tableUi->setCursor(Qt::PointingHandCursor);
    tableUi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableUi->verticalHeader()->setDefaultSectionSize(230);
    tableUi->horizontalHeader()->setDefaultSectionSize(154);
    tableUi->setFrameStyle(QFrame::NoFrame);
    tableUi->horizontalHeader()->hide();
    tableUi->verticalHeader() ->hide();
    tableUi->setStyleSheet
    (
        "QHeaderView::section { background-color:#073d69}\n"
        "QTableView QTableCornerButton::section { background-color:#073d69}"
    );
    tableUi->show();
}

void MovieView::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
    QStandardItem* movieData = new QStandardItem();

    QPixmap moviePoster = posterManager.getMoviePoster(movieId, "154");
    QList<QString> movieInfo = infoManager.getMovieInfo(movieId);

    movieData->setData(QVariant(moviePoster), Qt::DecorationRole);
    tableData->setItem(0, tableLine, movieData);
}

void MovieView::similarTableDoubleClick(const QModelIndex&)
{
    QModelIndexList selection = ui.similarMoviesTable->selectionModel()->selectedIndexes();
    
        ui.similarMoviesTable->setEnabled(false);
        for (int i = 0; i < selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            this->m_selectedMovieId = m_similarMovieIds[index.column()];
            MovieView* movieView = new MovieView(m_selectedMovieId, this);
            this->setMovieView();
        }
        ui.similarMoviesTable->setEnabled(true);
}
