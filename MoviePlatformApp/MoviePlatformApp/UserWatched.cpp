#include "UserWatched.h"

UserWatched::UserWatched()
{
}

UserWatched::UserWatched(int userId, std::string showId)
	: m_userId{ userId }, m_showId{ std::move(showId) } {}

UserWatched::~UserWatched()
{
}


void UserWatched::setShowId(std::string showId)
{
	m_showId = std::move(showId);
}

void UserWatched::setUserId(int userId)
{
	m_userId = userId;
}

std::string UserWatched::getShowId() const
{
	return m_showId;
}

int UserWatched::getUserId() const
{
	return m_userId;
}



