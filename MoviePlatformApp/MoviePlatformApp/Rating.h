#pragma once
#include<string>
class Rating
{
private:
	std::string m_showId;//fk to Movies
	int m_userId;//fk to User
	int m_numberOfStars; // (☆☆☆) from 0 to 5
public:
	Rating();
	Rating(std::string showId, int userId, int numberOfStars);
	~Rating();

	void setShowId(std::string showId);
	void setUserId(int userId);
	void setRating(int numberOfStars);

	std::string getShowId() const;
	int getUserId() const;
	int getRating() const;

};

