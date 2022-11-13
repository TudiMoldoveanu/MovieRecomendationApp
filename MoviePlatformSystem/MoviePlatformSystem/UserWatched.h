#pragma once
#include <string>
#include <optional>


class UserWatched
{

private:
	std::string m_id; // PK
	std::string m_userId; // FK
	std::string m_showId; // FK

public:
	UserWatched();
	UserWatched(std::string id, std::string userId, std::string showId);
	~UserWatched();

	void setId(const std::string& m_id);
	void setShowId(const std::string& showId);
	void setUserId(const std::string& userId);

	std::string getId() const;
	std::string getShowId() const;
	std::string getUserId() const;
};

