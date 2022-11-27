#pragma once
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_PreferencesPage.h"

class PreferencesPage : public QMainWindow
{
    Q_OBJECT

public:
    PreferencesPage(QWidget* parent = nullptr);
    ~PreferencesPage();


private:
    Ui::PreferencesPageClass ui;
};
