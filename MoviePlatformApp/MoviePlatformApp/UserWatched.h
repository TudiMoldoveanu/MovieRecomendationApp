#pragma once
#include <string>
#include <optional>


class UserWatched
{

private:
	int m_userId; // FK
	int m_showId; // FK

public:
	UserWatched();
	UserWatched(int userId, int showId);
	~UserWatched();

	void setShowId(int showId);
	void setUserId(int userId);

	int getShowId() const;
	int getUserId() const;
};

