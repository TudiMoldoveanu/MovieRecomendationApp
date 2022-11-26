#pragma once
#include <string>
#include <optional>


class UserWatched
{

private:
	int m_userId; // FK
	std::string m_showId; // FK

public:
	UserWatched();
	UserWatched(int userId, std::string showId);
	~UserWatched();

	void setShowId(std::string showId);
	void setUserId(int userId);

	std::string getShowId() const;
	int getUserId() const;
};

