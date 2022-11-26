#include "Rating.h"

Rating::Rating()
{
}

Rating::Rating(std::string showId, int userId, double rating)
	: m_showId{ showId }, m_userId{ userId }, m_rating{rating} {}

Rating::~Rating()
{
}

void Rating::setShowId(std::string showId)
{
	m_showId = std::move(showId);
}
void Rating::setUserId(int userId)
{
	m_userId = userId;
}
void Rating::setRating(double rating)
{
	m_rating = rating;
}


std::string Rating::getShowId() const
{
	return m_showId;
}
int Rating::getUserId() const
{
	return m_userId;
}
double Rating::getRating() const
{
	return m_rating;
}

