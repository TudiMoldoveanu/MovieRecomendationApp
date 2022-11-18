#include "UserPreferences.h"

UserPreferences::UserPreferences()
{

}

UserPreferences::UserPreferences(int userId, std::string showId) 
	: m_userId{ userId }, m_showId{ std::move(showId) } {}

UserPreferences::~UserPreferences()
{
}

void UserPreferences::setUserId(int userId)
{
	m_userId = userId;
}

void UserPreferences::setShowId(std::string showId)
{
	m_showId = std::move(showId);
}

std::string UserPreferences::getShowId() const
{
	return m_showId;
}

int UserPreferences::getUserId() const
{
	return m_userId;
}




