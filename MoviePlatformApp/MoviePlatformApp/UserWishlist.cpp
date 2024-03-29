#include "UserWishlist.h"

UserWishlist::UserWishlist()
{
}

UserWishlist::UserWishlist(int userId, int showId)
	: m_userId{ std::move(userId) },m_showId{ std::move(showId) } {}

UserWishlist::~UserWishlist()
{
}

void UserWishlist::setShowId(int showId)
{
	m_showId =showId;
}

void UserWishlist::setUserId(int userId)
{
	m_userId = userId;
}

int UserWishlist::getShowId() const
{
	return m_showId;
}

int UserWishlist::getUserId() const
{
	return m_userId;
}

