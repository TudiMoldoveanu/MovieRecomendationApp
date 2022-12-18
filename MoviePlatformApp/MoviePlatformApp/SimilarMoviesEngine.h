#pragma once

#include"DataBase.h"
#include"Movie.h"
#include <regex>

class SimilarMoviesEngine
{
private:

	Movie m_movie;
	Database* m_database = Database::connect();
	std::vector<Movie> allRecords = m_database->getAll<Movie>();

public:
	SimilarMoviesEngine(Movie movie);
	std::vector<int> getSimilarMoviesByGenreAndRating();
	std::vector<int>getSimilarMoviesByDirectorOrCast();
	Movie getMovie();
	void printMoviesId(const std::vector<int>& moviesId);
};

