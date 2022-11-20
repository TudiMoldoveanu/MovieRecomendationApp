#pragma once
#include <string>
#include <optional>

class UserWishlist
{
private:
	int m_userId; // FK
	std::string m_showId; // FK

public:
	UserWishlist();
	UserWishlist(int userId, std::string showId);
	~UserWishlist();

	void setShowId(std::string showId);
	void setUserId(int userId);

	std::string getShowId() const;
	int getUserId() const;
};

