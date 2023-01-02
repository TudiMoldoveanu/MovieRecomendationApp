#include "SimilarMoviesEngine.h"

SimilarMoviesEngine::SimilarMoviesEngine(Movie movie) : m_movie{ std::move(movie) }
{}


std::vector<int> SimilarMoviesEngine::getSimilarMoviesByGenreAndRating() 
{
	return m_database->getSimilarGenreAndRating(m_movie);
}


std::vector<int> SimilarMoviesEngine::getSimilarMoviesByDirectorOrCast() 
{
	return m_database->getSimilarDirectorOrCast(m_movie);
}

Movie SimilarMoviesEngine::getMovie() const
{
	return m_movie;
}

std::vector<int> SimilarMoviesEngine::getMoviesId()
{
	std::vector<int> similar1 = getSimilarMoviesByGenreAndRating();
	std::vector<int> similar2 = getSimilarMoviesByDirectorOrCast();

	if (similar1.empty() && similar2.empty()) {
		std::cout << "Didn't find any similar movies based on this criteria!" << std::endl;
	}
	else {
		std::move(similar2.begin(), similar2.end(), std::back_inserter(similar1));
	}
	
	return similar1;
}