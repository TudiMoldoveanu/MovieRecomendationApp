#pragma once
#include<string>
class Rating
{
private:
	int m_showId;//fk to Movies
	int m_userId;//fk to User
	int m_numberOfStars; // (☆☆☆) from 0 to 5
public:
	Rating();
	Rating(int showId, int userId, int numberOfStars);
	~Rating();

	void setShowId(int showId);
	void setUserId(int userId);
	void setRating(int numberOfStars);

	int getShowId() const;
	int getUserId() const;
	int getRating() const;

};

