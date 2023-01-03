#pragma once

#include "UserWatched.h"
#include"UserWishlist.h"
#include"DataBase.h"
#include"Movie.h"


class RecomendationEngine
{
private:
	Database* m_database = Database::connect();
	std::vector<int> m_wishlistedMovieIds, m_wacthedMovieIds;
	std::map < std::string, int> m_movieGenresOfUser;
	//Funtions
    std::array<std::string,2> getFirstTwoGenresOfMovie(const int& movieId);
	std:: string mostFreqGenre();
   

public:
	RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds);
	void setMovieGenresMap();
	std::vector<int> getSimilarMovies();
	 
};

