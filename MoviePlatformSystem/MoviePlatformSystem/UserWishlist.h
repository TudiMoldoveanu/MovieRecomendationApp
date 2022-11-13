#pragma once
#include <string>
#include <optional>

class UserWishlist
{
private:
	std::string m_id; // PK
	std::string m_userId; // FK
	std::string m_showId; // FK

public:
	UserWishlist();
	UserWishlist(std::string id, std::string userId, std::string showId);
	~UserWishlist();

	void setId(const std::string& id);
	void setShowId(const std::string& showId);
	void setUserId(const std::string& userId);

	std::string getId() const;
	std::string getShowId() const;
	std::string getUserId() const;
};

