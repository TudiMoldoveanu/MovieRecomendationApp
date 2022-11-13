#pragma once
#include<string>
class Rating
{
private:
	std::string m_id;//pk
	std::string m_showId;//fk to Movies
	std::string m_userId;//fk to User
	std::string m_rating;
public:
	Rating();
	Rating(std::string id, std::string showId, std::string userId, std::string rating);
	~Rating();

	void setId(const std::string& id);
	void setShowId(const std::string& showId);
	void setUserId(const std::string& userId);
	void setRating(const std::string& rating);

	std::string getId() const;
	std::string getShowId() const;
	std::string getUserId() const;
	std::string getRating() const;

};

