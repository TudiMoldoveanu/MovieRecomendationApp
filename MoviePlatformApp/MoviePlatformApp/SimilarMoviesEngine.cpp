#include "SimilarMoviesEngine.h"

SimilarMoviesEngine::SimilarMoviesEngine(const Movie& movie) :m_movie{ movie } {};


std::vector<int> SimilarMoviesEngine::getSimilarMoviesByGenreAndRating()
{

	std::vector<int> similarMovies;
	
	std::string allGenre= getMovie().getListedIn().value();

	//extract first genre
	std::string firstGenre;

	//extract letters until we find ,
	for (int i = 0; i < allGenre.size(); i++)
	{
		if (allGenre[i] != ',')
		{
			firstGenre += allGenre[i];
		}
		else break;
	}

	auto allRecords = m_database->getAll< Movie >();

	//returns first 2 movies that have the firstGenre substring in ListedIn
	int count = 0;
	for (int i = 0; i < allRecords.size(); i++)
	{
		if (count <= 1)
		{
			std::string mainString = allRecords[i].getListedIn().value();
			//test if mainString has firstGenre substring and if rating are the same
			if 
			(
			mainString.find(firstGenre) != std::string::npos && allRecords[i].getId()!=getMovie().getId() && 
			allRecords[i].getRating().value() == getMovie().getRating().value() )
			{
				similarMovies.push_back(allRecords[i].getId());
				count++;
			}
		}
		else
		{
			break;
		}

	}
	return similarMovies;
}

std::vector<int> SimilarMoviesEngine::getSimilarMoviesByDirectorOrCast()
{
	std::vector<int> similarMovies;

	std::string allCast = getMovie().getListedIn().value();

	//extract first cast member
	std::string firstCastMember;

	//extract letters until we find ,
	for (int i = 0; i < allCast.size(); i++)
	{
		if (allCast[i] != ',')
		{
			firstCastMember += allCast[i];
		}
		else break;
	}

	auto allRecords = m_database->getAll< Movie >();

	//returns first 2 movies that have the firstCastMember substring in cast
	int count = 0;
	for (int i = 0; i < allRecords.size(); i++)
	{
		if (count <= 1)
		{
			std::string mainString = allRecords[i].getCast().value();
			//test if mainString has firstCastMember substring or if directors are the same
			if
			(
			  (mainString.find(firstCastMember) != std::string::npos && allRecords[i].getId() != getMovie().getId()) ||
			  (allRecords[i].getDirector().value() == getMovie().getDirector().value() && allRecords[i].getId() != getMovie().getId())
			)
			{
				similarMovies.push_back(allRecords[i].getId());
				count++;
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

void SimilarMoviesEngine::printMoviesId(const std::vector<int>& moviesId)
{
	if (moviesId.empty())
	{
		std::cout << "Didn't find any similar movies based on this criteria!";

	}
	else 
	{
		for (int i = 0; i < moviesId.size(); i++)
		{
			std::cout << moviesId[i] << " ";
		}
	}
	std::cout << std::endl;
}


