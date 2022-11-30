#include "MovieView.h"

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
