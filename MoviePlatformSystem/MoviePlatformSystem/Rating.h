#pragma once
#include<string>
class Rating
{
private:
	std::string m_showId;//fk to Movies
	int m_userId;//fk to User
	double m_rating;
public:
	Rating();
	Rating(std::string showId, int userId, double rating);
	~Rating();

	void setShowId(std::string showId);
	void setUserId(int userId);
	void setRating(double rating);

	std::string getShowId() const;
	int getUserId() const;
	double getRating() const;

};

