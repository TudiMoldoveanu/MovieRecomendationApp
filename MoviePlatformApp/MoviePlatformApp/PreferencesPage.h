#pragma once
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_PreferencesPage.h"
#include "DataBase.h"
#include <QtWidgets>
#include <ctime>
#include "PosterManager.h"

class PreferencesPage : public QMainWindow
{
    Q_OBJECT

public:
    PreferencesPage(QWidget* parent = nullptr);
    ~PreferencesPage();
    void setMovieData(const int& tableLine, const int& movieId, QStandardItemModel* tableData);
    void assignDataToTable(QTableView* tableUi, QStandardItemModel* tableData);
    void setMoviePosters(const int& fromId, const int& toId);
private slots:
    void on_allDoneButton_clicked();
private:
    Ui::PreferencesPageClass ui;
    Database* database = Database::connect();
    std::vector<Movie> m_allMovies;
    QStandardItemModel* m_moviePosters;
    PosterManager posterManager;
};
