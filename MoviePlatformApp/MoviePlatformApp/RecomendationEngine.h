#pragma once

#include "UserWatched.h"
#include"UserWishlist.h"
#include"DataBase.h"
#include"Movie.h"
#include <unordered_set>


class RecomendationEngine
{
private:
	Database* m_database = Database::connect();
	std::vector<int> m_wishlistedMovieIds, m_wacthedMovieIds;
	std::map < std::string, int> m_movieGenresOfUser;
	std::map < std::string, double> m_movieGenres;
	std::unordered_set<int> m_watchedAndWishlistMovies;
	std::set<int> m_recommendedMoviesVector;
	//Functions
	std::string getFirstGenreOfMovie(const int& movieId);
	std:: string mostFreqGenre();
	void setUserGenreFrequency();
	std::string RandomizeByProbabilityGenre();
	double randomizeNumber();
   
public:
	RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds);
	void setMovieGenresMap();
	std::set<int> getSimilarMovies();
	 
};

