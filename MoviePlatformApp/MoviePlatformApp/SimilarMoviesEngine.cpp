#include "SimilarMoviesEngine.h"

SimilarMoviesEngine::SimilarMoviesEngine(Movie movie) : m_movie{ std::move(movie) }
{}

// TO be improved using transaction, refactor it by removing nested if-elses and maybe to try another approach
std::vector<int> SimilarMoviesEngine::getSimilarMoviesByGenreAndRating() 
{

	std::vector<int> similarMovies;
	
	std::string allGenre = getMovie().getListedIn().value();
	//extract letters until we find ,
	std::string delimiter = ",";
	std::string firstGenre = allGenre.substr(0, allGenre.find(delimiter));

	//returns first 3 movies that have the firstGenre substring in ListedIn
	int count = 0;
	for (const auto& record : allRecords)
	{
		if (count <= 2)
		{
			std::string mainString = record.getListedIn().value();
			//test if mainString has firstGenre substring and if rating are the same
			if (m_movie.getId() != record.getId())
			{
				if (mainString.find(firstGenre) != std::string::npos && *record.getRating() == *m_movie.getRating())
				{
					similarMovies.push_back(record.getId());
					count++;
				}
			}
		}
		else
			break;
		
	}
	return similarMovies;
}

// TO be improved using transaction, to add checks for all cast members and refactor it by removing nested if-elses
std::vector<int> SimilarMoviesEngine::getSimilarMoviesByDirectorOrCast() 
{
	std::vector<int> similarMovies;
	std::string allCast = m_movie.getCast().value();
	std::string delimiter = ",";
	std::string firstCastMember = allCast.substr(0, allCast.find(delimiter));

	//returns first 3 movies that have the firstCastMember substring in cast
	int count = 0;
	for (const auto& record : allRecords)
	{
		if (count <= 2)
		{
			std::string mainString = record.getCast().value();
			if (m_movie.getId() != record.getId())
			{
				if (mainString.find(firstCastMember) != std::string::npos || *record.getDirector() == *m_movie.getDirector() && *m_movie.getDirector() != "")
				{
					similarMovies.push_back(record.getId());
					count++;
				}
			}
		}
		else
		{
			break;
		}
	}
    return similarMovies;
}

Movie SimilarMoviesEngine::getMovie()
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