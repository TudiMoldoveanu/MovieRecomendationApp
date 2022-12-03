#include "MovieView.h"
#include "stardelegate.h"
#include "starrating.h"
#include <QTableWidget>

MovieView::MovieView(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MovieView::~MovieView()
{}

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
    ui.tableWidget->setItemDelegate(new StarDelegate);
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked
        | QAbstractItemView::SelectedClicked);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget->horizontalHeader()->hide();
    ui.tableWidget->verticalHeader()->hide();
    ui.tableWidget->setFrameStyle(QFrame::NoFrame);
    ui.tableWidget->setShowGrid(false);
    //hide highlight
    setStyleSheet("QTableWidget {background-color: transparent;}"
        "QHeaderView::section {background-color: transparent;}"
        "QHeaderView {background-color: transparent;}"
        "QTableCornerButton::section {background-color: transparent;}");
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
