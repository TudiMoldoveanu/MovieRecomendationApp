#include "MovieView.h"
#include "stardelegate.h"
#include "starrating.h"
#include <QTableWidget>

MovieView::MovieView(int selectedMovieId, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    m_selectedMovieId = selectedMovieId;
}

MovieView::~MovieView()
{}

void MovieView::setMovieView() {
    Movie movie = database->getById<Movie>(m_selectedMovieId);

    //created an instance of SimilarMoviesEngine
    SimilarMoviesEngine similarMovies(movie);
    std::vector<int> similar1 = similarMovies.getMoviesId(similarMovies.getSimilarMoviesByGenreAndRating());
    std::vector<int> similar2 = similarMovies.getMoviesId(similarMovies.getSimilarMoviesByDirectorOrCast());

    if (!similar1.empty()) {
        if (similar1.size() > 0) {
            QPixmap moviePoster1 = posterManager.getMoviePoster(similar1[0], "154");
            ui.similarMovie1->setPixmap(moviePoster1);
        }
        if (similar1.size() > 1) {
            QPixmap moviePoster2 = posterManager.getMoviePoster(similar1[1], "154");
            ui.similarMovie2->setPixmap(moviePoster2);
        }
        if (similar1.size() > 2) {
            QPixmap moviePoster3 = posterManager.getMoviePoster(similar1[2], "154");
            ui.similarMovie3->setPixmap(moviePoster3);
        }
    }

    if (!similar2.empty()) {
        if (similar2.size() > 0) {
            QPixmap moviePoster4 = posterManager.getMoviePoster(similar2[0], "154");
            ui.similarMovie4->setPixmap(moviePoster4);
        }
        if (similar2.size() > 1) {
            QPixmap moviePoster5 = posterManager.getMoviePoster(similar2[1], "154");
            ui.similarMovie5->setPixmap(moviePoster5);
        }
        if (similar2.size() > 2) {
            QPixmap moviePoster6 = posterManager.getMoviePoster(similar2[2], "154");
            ui.similarMovie6->setPixmap(moviePoster6);
        }
    }

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
    for (int i = 0; i < wishlistedMovieIds.size(); i++) {
        if (m_selectedMovieId == wishlistedMovieIds[i]) {
            ui.wishlistButton->setText("Remove Wishlist");
            ui.wishlistButton->setStyleSheet("background-color: rgb(139,0,0)");
            break;
        }
    }
    for (int i = 0; i < watchedMovieIds.size(); i++) {
        if (m_selectedMovieId == watchedMovieIds[i]) {
            ui.watchedButton->setText("Remove Watched");
            ui.watchedButton->setStyleSheet("background-color: rgb(139,0,0)");
            break;
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
    UserWatched userWatched(userId, m_selectedMovieId);
    if (ui.watchedButton->text().toStdString() == "Remove Watched") {
        database->deleteId<UserWatched>(userId, m_selectedMovieId);
        ui.watchedButton->setText("Mark as Watched");
        ui.watchedButton->setStyleSheet("background-color: rgb(204,204,0)");
    }
    else {
        database->replace(userWatched);
        ui.watchedButton->setText("Remove Watched");
        ui.watchedButton->setStyleSheet("background-color: rgb(139,0,0)");
    }
}

void MovieView::on_wishlistButton_clicked()
{
    int userId = loggedUser->getId();
    UserWishlist userWishlist(userId, m_selectedMovieId);
    if (ui.wishlistButton->text().toStdString() == "Remove Wishlist") {
        database->deleteId<UserWishlist>(userId, m_selectedMovieId);
        ui.wishlistButton->setText("Add to Wishlist");
        ui.wishlistButton->setStyleSheet("background-color: rgb(204,204,0)");
    }
    else {
        database->replace(userWishlist);
        ui.wishlistButton->setText("Remove Wishlist");
        ui.wishlistButton->setStyleSheet("background-color: rgb(139,0,0)");
    }
}
