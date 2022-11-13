#include "UserPreferences.h"

UserPreferences::UserPreferences()
{

}

UserPreferences::UserPreferences(std::string id, std::string showId) 
	:m_id{ id }, m_showId{ showId } {}

UserPreferences::~UserPreferences()
{
}

void UserPreferences::setId(const std::string& id)
{
	m_id = id;
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




