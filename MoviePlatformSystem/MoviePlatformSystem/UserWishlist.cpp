#include "UserWishlist.h"

UserWishlist::UserWishlist()
{
}

UserWishlist::UserWishlist(std::string id, std::string show_id)
	:m_id{ id }, m_show_id{ std::move(show_id) } {}

UserWishlist::~UserWishlist()
{
}

void UserWishlist::setId(const std::string& id)
{
	m_id = id;
}

void UserWishlist::setShowId(const std::string& show_id)
{
	m_show_id = std::move(show_id);
}

std::string UserWishlist::getShowId() const
{
	return m_show_id;
}

std::string UserWishlist::getId() const
{
	return m_id;
}


