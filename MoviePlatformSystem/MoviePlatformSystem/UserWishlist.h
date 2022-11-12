#pragma once
#include <string>
#include <optional>

class UserWishlist
{
private:
	std::string m_id; // PK
	std::string m_show_id; // FK

public:
	UserWishlist();
	UserWishlist(std::string id, std::string show_id);
	~UserWishlist();

	void setId(const std::string& m_id);
	void setShowId(const std::string& show_id);

	std::string getId() const;
	std::string getShowId() const;
};

