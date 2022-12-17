#pragma once

#include"DataBase.h"
#include"Movie.h"

class SimilarMoviesEngine
{
private:

	Movie m_movie;
	Database* m_database = Database::connect();

public:
	SimilarMoviesEngine(const Movie& movie);
	std::vector<int> getSimilarMoviesByGenreAndRating();
	std::vector<int>getSimilarMoviesByDirectorOrCast();
	Movie getMovie();
	void printMoviesId(const std::vector<int>& moviesId);
};

