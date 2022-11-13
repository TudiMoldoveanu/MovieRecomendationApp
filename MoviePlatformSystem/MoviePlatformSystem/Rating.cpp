#include "Rating.h"

Rating::Rating()
{
}

Rating::Rating(std::string id, std::string showId, std::string userId, std::string rating)
	:m_id{ id }, m_showId{ showId }, m_userId{ userId }, m_rating{rating} {}

Rating::~Rating()
{
}

void Rating::setId(const std::string& id)
{
	m_id = id;
}
void Rating::setShowId(const std::string& showId)
{
	m_showId = showId;
}
void Rating::setUserId(const std::string& userId)
{
	m_userId = userId;
}
void Rating::setRating(const std::string& rating)
{
	m_rating = rating;
}

std::string Rating::getId() const
{
	return m_id;
}
std::string Rating::getShowId() const
{
	return m_showId;
}
std::string Rating::getUserId() const
{
	return m_userId;
}
std::string Rating::getRating() const
{
	return m_rating;
}

