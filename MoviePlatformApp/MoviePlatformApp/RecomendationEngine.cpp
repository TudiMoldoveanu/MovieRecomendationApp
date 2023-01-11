#include "RecomendationEngine.h"

RecomendationEngine::RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds) :m_wacthedMovieIds{ watchedIds }, m_wishlistedMovieIds{ wishlistIds } {}

void RecomendationEngine::setMovieGenresMap()
{
	for (int i = 0; i < m_wacthedMovieIds.size(); i++)
	{
		int currentId = m_wacthedMovieIds[i];
		std::string gernre = getFirstGenreOfMovie(currentId);
		m_movieGenresOfUser[gernre]++;
		
	}
	for (int i = 0; i < m_wishlistedMovieIds.size(); i++)
	{
		int currentId = m_wacthedMovieIds[i];
		std::string gernre = getFirstGenreOfMovie(currentId);
		m_movieGenresOfUser[gernre]++;
		
	}

}

std::vector<int> RecomendationEngine::getSimilarMovies()
{
	return m_database->getSimilarGenre(mostFreqGenre());
}

std::string RecomendationEngine::getFirstGenreOfMovie(const int& movieId)
{
    std::string firstGenre;
	Movie movie = m_database->getById<Movie>(movieId);

	std::string allMovieGenres = movie.getListedIn().value();
	std::string delimiter = ",";

	firstGenre = allMovieGenres.substr(0, allMovieGenres.find(delimiter));
	
	return firstGenre;
}

std::string RecomendationEngine::mostFreqGenre()
{
	int max = 0;
	std::string genre;
	std::map < std::string, int>::iterator it;
	for (it=m_movieGenresOfUser.begin(); it!=m_movieGenresOfUser.end(); it++)
	{
		if (max < it->second)
		{
			max = it->second;
			genre = it->first;
		}
	}
	return genre;
}


