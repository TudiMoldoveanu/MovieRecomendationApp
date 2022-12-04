#include "Rating.h"

Rating::Rating()
{
}

Rating::Rating(int showId, int userId, int numberOfStars)
	: m_showId{ showId }, m_userId{ userId }, m_numberOfStars{numberOfStars} {}

Rating::~Rating()
{
}

void Rating::setShowId(int showId)
{
	m_showId = showId;
}
void Rating::setUserId(int userId)
{
	m_userId = userId;
}
void Rating::setRating(int numberOfStars)
{
	m_numberOfStars = numberOfStars;
}


int Rating::getShowId() const
{
	return m_showId;
}
int Rating::getUserId() const
{
	return m_userId;
}
int Rating::getRating() const
{
	return m_numberOfStars;
}

