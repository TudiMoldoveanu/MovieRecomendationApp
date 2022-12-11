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

void PreferencesPage::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
    const QSize btnSize = QSize(140, 92);
    for (int col = 0; col < tableSize; col++)
    {
        QStandardItem* movieData = new QStandardItem();
        int random = 1 + (rand() % 3000);
        QPixmap moviePoster = getMoviePoster(random, "92");
        movieData->setData(QVariant(moviePoster), Qt::DecorationRole);
        tableData->setItem(col, tableLine, movieData);
    }
}

void PreferencesPage::setMoviePosters(const int& fromId, const int& toId)
{
    for (int i = fromId; i < toId; i++) {
        setMovieData(i, i + 1, m_moviePosters);
    }

    assignDataToTable(ui.tableView, m_moviePosters);
}

QPixmap PreferencesPage::getMoviePoster(const int& id, const std::string& size) {

    Movie movie = database->getById<Movie>(id);

    std::string moviePosterUrl = std::move(*movie.getPosterUrl());
    std::string movieTitle = std::move(*movie.getPosterUrl());

    QUrl requestUrl;

    QString finalUrl = "https://image.tmdb.org/t/p/w" + QString::fromStdString(size) + QString::fromStdString(moviePosterUrl);
    requestUrl = QUrl(finalUrl);

    return downloadMoviePoster(requestUrl);
}

QPixmap PreferencesPage::downloadMoviePoster(QUrl url) {

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
