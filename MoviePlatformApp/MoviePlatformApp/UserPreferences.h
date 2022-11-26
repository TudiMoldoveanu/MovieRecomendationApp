#pragma once
#include <string>

class UserPreferences
{
private:
	int m_userId; //fk to user
	std::string m_showId;//fk to movies

public:
	UserPreferences();
	UserPreferences(int userId, std::string showId);
	~UserPreferences();

	void setUserId(int userId);
	void setShowId(std::string showId);

	std::string getShowId()const;
	int getUserId()const;
};

