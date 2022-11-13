#include "UserPreferences.h"

UserPreferences::UserPreferences()
{

}

UserPreferences::UserPreferences(std::string id, std::string userId, std::string showId) 
	:m_id{ id }, m_userId{ userId }, m_showId{ showId } {}

UserPreferences::~UserPreferences()
{
}

void UserPreferences::setId(const std::string& id)
{
	m_id = std::move(id);
}

void UserPreferences::setUserId(const std::string& userId)
{
	m_userId = std::move(userId);
}

void UserPreferences::setShowId(const std::string& showId)
{
	m_showId = std::move(showId);
}

std::string UserPreferences::getId() const
{
	return m_id;
}

std::string UserPreferences::getShowId() const
{
	return m_showId;
}

std::string UserPreferences::getUserId() const
{
	return m_userId;
}




