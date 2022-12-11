#include "PreferencesPage.h"
#include "LogInPage.h"
#include "Movie.h"
#include<QSize>

const int tableSize = 7;
PreferencesPage::PreferencesPage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_allMovies = database->getAll<Movie>();
    m_moviePosters = new QStandardItemModel();
    setMoviePosters(0, tableSize);
}

PreferencesPage::~PreferencesPage() {}