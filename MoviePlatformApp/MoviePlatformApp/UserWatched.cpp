#include "UserWatched.h"

UserWatched::UserWatched()
{
}

UserWatched::UserWatched(int userId, int showId)
	: m_userId{ userId }, m_showId{ showId } {}

UserWatched::~UserWatched()
{
}


void UserWatched::setShowId(int showId)
{
	m_showId = showId;
}

void UserWatched::setUserId(int userId)
{
	m_userId = userId;
}

int UserWatched::getShowId() const
{
	return m_showId;
}

int UserWatched::getUserId() const
{
	return m_userId;
}



