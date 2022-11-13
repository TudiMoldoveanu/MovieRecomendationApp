#pragma once
#include <string>
class UserPreferences
{
private:
	std::string m_id;//pk
	std::string m_userId; //fk to user
	std::string m_showId;//fk to movies

public:
	UserPreferences();
	UserPreferences(std::string id, std::string userId, std::string showId);
	~UserPreferences();

	void setId(const std::string& id);
	void setUserId(const std::string& userId);
	void setShowId(const std::string& showId);

	std::string getId()const;
	std::string getShowId()const;
	std::string getUserId()const;
};

