#include "UserWatched.h"

UserWatched::UserWatched()
{
}

UserWatched::UserWatched(std::string id, std::string show_id)
	:m_id{ id }, m_show_id{ std::move(show_id) } {}

UserWatched::~UserWatched()
{
}

void UserWatched::setId(const std::string& id)
{
	m_id = id;
}

void UserWatched::setShowId(const std::string& show_id)
{
	m_show_id = std::move(show_id);
}

std::string UserWatched::getShowId() const
{
	return m_show_id;
}

std::string UserWatched::getId() const
{
	return m_id;
}


