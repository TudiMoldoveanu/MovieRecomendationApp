#include "SimilarMoviesEngine.h"

SimilarMoviesEngine::SimilarMoviesEngine(const Movie& movie) :m_movie{ movie } {};


std::vector<int> SimilarMoviesEngine::getSimilarMoviesByGenre()
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

	//returns first 3 movies that have the firstGenre substring in ListedIn
	int count = 0;
	for (int i = 0; i < allRecords.size(); i++)
	{
		if (count <= 2)
		{
			std::string mainString = allRecords[i].getListedIn().value();
			//test if mainString has firstGenre substring
			if (mainString.find(firstGenre) != std::string::npos && allRecords[i].getId()!=getMovie().getId())
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
	for (int i = 0; i < moviesId.size(); i++)
	{
		std::cout<<moviesId[i]<<" ";
	}
}


