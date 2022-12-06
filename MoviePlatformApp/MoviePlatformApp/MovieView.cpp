#include "MovieView.h"
#include "stardelegate.h"
#include "starrating.h"
#include <QTableWidget>

MovieView::MovieView(std::optional<User> loggedUser, int selectedMovieId, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    m_loggedUser = loggedUser;
    m_selectedMovieId = selectedMovieId;
}

MovieView::~MovieView()
{}

void MovieView::setMovieView(QList<QString> movieInfo, QPixmap moviePoster) {
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
    static constexpr struct {
        int rating;
    } staticData[] = {
        { 5 }
    };

    ui.tableWidget->setColumnCount(1);
    ui.tableWidget->setRowCount(1);
    ui.tableWidget->setItemDelegate(new StarDelegate(m_loggedUser, m_selectedMovieId));
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget->horizontalHeader()->hide();
    ui.tableWidget->verticalHeader()->hide();
    ui.tableWidget->setFrameStyle(QFrame::NoFrame);
    ui.tableWidget->setShowGrid(false);
    ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    //populate
    QTableWidgetItem* rating = new QTableWidgetItem;
    rating->setData(0, QVariant::fromValue(StarRating(staticData[0].rating)));
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
    int userId = m_loggedUser.value().getId();
    UserWatched userWatched(userId, m_selectedMovieId);
    database->replace(userWatched);
    ui.watchedButton->setEnabled(false);
    ui.watchedButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
}

void MovieView::on_wishlistButton_clicked()
{
    int userId = m_loggedUser.value().getId();
    UserWishlist userWishlist(userId, m_selectedMovieId);
    database->replace(userWishlist);
    ui.wishlistButton->setEnabled(false);
    ui.wishlistButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
}
