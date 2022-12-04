#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>

#include "starrating.h"
#include "Database.h"

//! [0]
class StarEditor : public QWidget
{
    Q_OBJECT
public:
    StarEditor(std::optional<User> loggedUser, int selectedMovieId, QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setStarRating(const StarRating &starRating) {
        myStarRating = starRating;
    }
    StarRating starRating() { return myStarRating; }

signals:
    void editingFinished();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int starAtPosition(int x) const;
    std::optional<User> m_loggedUser;
    int m_selectedMovieId;
    StarRating myStarRating;
    Database* database = Database::connect();
};
//! [0]

#endif
