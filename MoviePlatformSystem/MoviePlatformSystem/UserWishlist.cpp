#include "UserWishlist.h"

UserWishlist::UserWishlist()
{
}

UserWishlist::UserWishlist(int userId, std::string showId)
	: m_userId{ std::move(userId) },m_showId{ std::move(showId) } {}

UserWishlist::~UserWishlist()
{
}

void UserWishlist::setShowId(std::string showId)
{
	m_showId = std::move(showId);
}

void UserWishlist::setUserId(int userId)
{
	m_userId = userId;
}

std::string UserWishlist::getShowId() const
{
	return m_showId;
}

int UserWishlist::getUserId() const
{
	return m_userId;
}

