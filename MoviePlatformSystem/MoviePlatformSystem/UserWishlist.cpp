#include "UserWishlist.h"

UserWishlist::UserWishlist()
{
}

UserWishlist::UserWishlist(std::string id, std::string userId, std::string showId)
	:m_id{ id }, m_userId{ std::move(userId) },m_showId{ std::move(showId) } {}

UserWishlist::~UserWishlist()
{
}

void UserWishlist::setId(const std::string& id)
{
	m_id = id;
}

void UserWishlist::setShowId(const std::string& showId)
{
	m_showId = std::move(showId);
}

void UserWishlist::setUserId(const std::string& userId)
{
	m_userId = std::move(userId);
}

std::string UserWishlist::getShowId() const
{
	return m_showId;
}

std::string UserWishlist::getUserId() const
{
	return m_userId;
}

std::string UserWishlist::getId() const
{
	return m_id;
}


