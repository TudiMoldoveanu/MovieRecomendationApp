#include "Rating.h"

Rating::Rating()
{
}

Rating::Rating(std::string showId, int userId, int numberOfStars)
	: m_showId{ showId }, m_userId{ userId }, m_numberOfStars{numberOfStars} {}

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
void Rating::setRating(int numberOfStars)
{
	m_numberOfStars = numberOfStars;
}


std::string Rating::getShowId() const
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

