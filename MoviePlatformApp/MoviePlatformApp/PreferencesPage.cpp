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

void PreferencesPage::on_allDoneButton_clicked()
{
    ui.allDoneButton->setEnabled(false);
    ui.allDoneButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);");
    LogInPage* logInPage;
    logInPage = new LogInPage(this);
    this->setVisible(false);
    logInPage->show();
    ui.allDoneButton->setEnabled(true);
    ui.allDoneButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
        "border-radius:10px;\n"
        "gridline-color: rgb(172, 81, 1);\n"
        "background-color: rgb(255, 204, 1);"));
}

void PreferencesPage::setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData)
{
    srand(time(0));
    const QSize btnSize = QSize(140, 92);
    for (int col = 0; col < tableSize; col++)
    {
        QStandardItem* movieData = new QStandardItem();
        int random = 1 + (rand() % m_allMovies.size());
        QPixmap moviePoster = posterManager.getMoviePoster(random, "92");
        movieData->setData(QVariant(moviePoster), Qt::DecorationRole);
        tableData->setItem(col, tableLine, movieData);
    }
}

void PreferencesPage::assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData) {

    //set data
    tableUi->setModel(tableData);
    //set styling
    tableUi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableUi->setSelectionMode(QAbstractItemView::MultiSelection);
    tableUi->setSelectionBehavior(QAbstractItemView::SelectItems);
    tableUi->verticalHeader()->setDefaultSectionSize(140);
    tableUi->horizontalHeader()->setDefaultSectionSize(92);
    tableUi->setStyleSheet
    (
        "QHeaderView::section { background-color:#073d69}\n"
        "QTableView QTableCornerButton::section { background-color:#073d69}"
    );
    tableUi->show();
}

void PreferencesPage::setMoviePosters(const int& fromId, const int& toId)
{
    for (int i = fromId; i < toId; i++) {
        setMovieData(i, i + 1, m_moviePosters);
    }

    assignDataToTable(ui.tableView, m_moviePosters);
}