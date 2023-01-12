#include "RecomendationEngine.h"

RecomendationEngine::RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds) :m_wacthedMovieIds{ watchedIds }, m_wishlistedMovieIds{ wishlistIds } 
{
	for (const auto& currentId : m_wishlistedMovieIds)
		m_watchedAndWishlistMovies.insert(currentId);

	for (const auto& currentId : m_wacthedMovieIds)
		m_watchedAndWishlistMovies.insert(currentId);
	srand(time(0));
}




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

std::set<int> RecomendationEngine::getSimilarMovies()
{
	// get 5 movies with the most frequent genre found in watched + wishlist
	m_database->getSimilarGenre(mostFreqGenre(), m_recommendedMoviesVector);

	// get 5 movies based on genre percent probability
	for (int i = 0; i < 5; i++)
	{
		std::string genreStr = RandomizeByProbabilityGenre();
		m_database->getSimilarGenre(genreStr, m_recommendedMoviesVector, true);
	}

	return m_recommendedMoviesVector;
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

void RecomendationEngine::setUserGenreFrequency()
{
	for (const auto& currentMovieId : m_watchedAndWishlistMovies)
	{
		std::string genre = getFirstGenreOfMovie(currentMovieId);
		m_movieGenres[genre]++;
	}

	for (auto& movieGenre : m_movieGenres)
		++movieGenre.second /= m_watchedAndWishlistMovies.size();
}

double RecomendationEngine::randomizeNumber()
{
	return ((double)rand()) / RAND_MAX;
}

std::string RecomendationEngine::RandomizeByProbabilityGenre()
{
	setUserGenreFrequency();
	double random = randomizeNumber();
	double firstIntervalMargin = 0;
	double secondIntervalMargin;
	for (const auto& movieGenreAndProbability : m_movieGenres)
	{
		secondIntervalMargin = firstIntervalMargin + movieGenreAndProbability.second;

		if (random >= firstIntervalMargin && random <= secondIntervalMargin)
			return movieGenreAndProbability.first;

		firstIntervalMargin += movieGenreAndProbability.second;
	}
}


