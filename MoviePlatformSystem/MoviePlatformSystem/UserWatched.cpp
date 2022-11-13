#include "UserWatched.h"

UserWatched::UserWatched()
{
}

UserWatched::UserWatched(std::string id, std::string userId, std::string showId)
	:m_id{ id }, m_userId{ std::move(userId) }, m_showId{ std::move(showId) } {}

UserWatched::~UserWatched()
{
}

void UserWatched::setId(const std::string& id)
{
	m_id = id;
}

void UserWatched::setShowId(const std::string& showId)
{
	m_showId = std::move(showId);
}

void UserWatched::setUserId(const std::string& userId)
{
	m_userId = std::move(userId);
}

std::string UserWatched::getShowId() const
{
	return m_showId;
}

std::string UserWatched::getUserId() const
{
	return m_userId;
}

std::string UserWatched::getId() const
{
	return m_id;
}


