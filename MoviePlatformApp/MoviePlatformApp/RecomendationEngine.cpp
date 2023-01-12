#include "RecomendationEngine.h"

RecomendationEngine::RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds) :m_wacthedMovieIds{ watchedIds }, m_wishlistedMovieIds{ wishlistIds } {}

void RecomendationEngine::setMovieGenresMap()
{
	for (const auto& currentId : m_wishlistedMovieIds)
	{
		std::string gernre = getFirstGenreOfMovie(currentId);
		m_movieGenresOfUser[gernre]++;
	}

	for (const auto& currentId : m_wacthedMovieIds)
	{
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
	for (const auto& genreCount : m_movieGenresOfUser)
	{
		if (max < genreCount.second)
		{
			max = genreCount.second;
			genre = genreCount.first;
		}
	}
	return genre;
}


