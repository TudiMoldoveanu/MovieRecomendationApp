#pragma once
#include <string>
#include <optional>

class UserWishlist
{
private:
	int m_userId; // FK
	int m_showId; // FK

public:
	UserWishlist();
	UserWishlist(int userId, int showId);
	~UserWishlist();

	void setShowId(int showId);
	void setUserId(int userId);

	int getShowId() const;
	int getUserId() const;
};

