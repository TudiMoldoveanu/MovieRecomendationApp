#include "RecomendationEngine.h"

RecomendationEngine::RecomendationEngine(std::vector<int> watchedIds, std::vector<int> wishlistIds) :m_wacthedMovieIds{ watchedIds }, m_wishlistedMovieIds{ wishlistIds } {}

void RecomendationEngine::setMovieGenresMap()
{
	for (int i = 0; i < m_wacthedMovieIds.size(); i++)
	{
		int currentId = m_wacthedMovieIds[i];
		std::array<std::string, 2> firstTwoGenres = getFirstTwoGenresOfMovie(currentId);
		//unpack the data from genre array 
		auto [firstGenre, secondGenre] = firstTwoGenres;
		m_movieGenresOfUser[firstGenre]++;
		m_movieGenresOfUser[secondGenre]++;
	}
	for (int i = 0; i < m_wishlistedMovieIds.size(); i++)
	{
		int currentId = m_wishlistedMovieIds[i];
		std::array<std::string, 2> firstTwoGenres = getFirstTwoGenresOfMovie(currentId);
		//unpack the data from genre array 
		auto [firstGenre, secondGenre] = firstTwoGenres;
		m_movieGenresOfUser[firstGenre]++;
		m_movieGenresOfUser[secondGenre]++;
	}

}

std::array<std::string, 2> RecomendationEngine::getFirstTwoGenresOfMovie(int movieId)
{
	std::array<std::string, 2> firstTwoGenres;
	Movie movie = m_database->getById<Movie>(movieId);

	std::string allMovieGenres = movie.getListedIn().value();
	std::string delimiter = ",";

	std::string firstGenre = allMovieGenres.substr(0, allMovieGenres.find(delimiter));
	firstTwoGenres[0] = firstGenre;

	std::string secondGenre = allMovieGenres.substr(firstGenre.size()+2, allMovieGenres.find(delimiter));
	firstTwoGenres[1] = secondGenre;

	return firstTwoGenres;
	
}


