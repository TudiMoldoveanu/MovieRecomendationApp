#include "Database.h"
#include "SimilarMoviesEngine.h"
#include <random>

Database::Database()
{
	 m_storage = std::make_unique<Storage>(initStorage("moviePlatform.sqlite"));

	 this->m_storage->sync_schema();

	 auto initMoviesCount = this->m_storage->count<Movie>();
	 if (initMoviesCount == 0)
		 this->PopulateStorage("movies_dataset.csv");

	 std::cout << "Database connected!" << std::endl; 
}

Database* Database::getInstance()
{
	static Database* database;
	if (database == nullptr)
	{
		database = new Database();
	}
	return database;


}

Database* Database::connect()
{
	return getInstance();
}

bool Database::isRegistered(const std::string& username)
{
	using namespace sqlite_orm;
	auto commited = m_storage->transaction([&]() mutable {
		auto userCount = m_storage->get_all<User>(where(c(&User::getUsername) == username));
	if (userCount.size() > 0) {  //  dummy condition for test
		return false;
		//  exits lambda and calls ROLLBACK
	}
	return true;        //  exits lambda and calls COMMIT
		});
	if (commited)
	{
		return false;
	}
	else {
		return true;
	}
}
bool Database::userAlreadyRated(const int& userId, const int& selectedMovieId)
{
	using namespace sqlite_orm;
	auto commited = m_storage->transaction([&]() mutable {
		auto userCount = m_storage->get_all<Rating>(where(c(&Rating::getUserId) == userId && c(&Rating::getShowId) == selectedMovieId));
	if (userCount.size() == 1) {  //  dummy condition for test
		return true;
		//  exits lambda and calls ROLLBACK
	}
	return false;        //  exits lambda and calls COMMIT
		});
	
	return commited;
}

std::vector<int> Database::getSimilarGenreAndRating(const Movie& movie)
{
	using namespace sqlite_orm;
	std::vector<int> similarMovies;

	std::string allGenre = movie.getListedIn().value();
	//extract letters until we find ,
	std::string delimiter = ",";
	std::string firstGenre = allGenre.substr(0, allGenre.find(delimiter));
	
	int count = 0;
	for (auto& record : m_storage->iterate<Movie>())
	{

		if(count > 2)
			break;

		if (movie.getId() == record.getId())
			continue;

		std::string mainString = record.getListedIn().value();
		//test if mainString has firstGenre substring and if rating are the same
		if (mainString.find(firstGenre) == std::string::npos || *record.getRating() != movie.getRating())
			continue;

		similarMovies.push_back(record.getId());
		count++;
	}

	return similarMovies;
}

std::vector<int> Database::getSimilarDirectorOrCast(const Movie& movie)
{
	using namespace sqlite_orm;
	std::vector<int> similarMovies;
	std::string allCast = movie.getCast().value();

	if (allCast == "")
		return similarMovies;

	std::string delimiter = ",";
	std::string firstCastMember = allCast.substr(0, allCast.find(delimiter));

	int count = 0;
	for (auto& record : m_storage->iterate<Movie>())
	{
		if (count > 2)
			break;

		std::string mainString = record.getCast().value();

		if (movie.getId() == record.getId())
			continue;

		if (mainString.find(firstCastMember) == std::string::npos && *record.getDirector() != movie.getDirector() || movie.getDirector() == "")
			continue;

		similarMovies.push_back(record.getId());
		count++;
	}

	return similarMovies;
}

std::vector<int> Database::getSimilarGenre(const std::string genre)
{
	using namespace sqlite_orm;
	std::vector<int> similarMovies;

	auto allMovies = getAll<Movie>();

	//pick a random index in movies vector
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(0, allMovies.size()); 
	int randomIndex = distr(gen);


	auto randomIt = allMovies.begin();
	std::advance(randomIt, randomIndex);

	int count = 0;
	for (auto it = randomIt;it!=allMovies.end();it++)
	{

		if (count > 5)
			break;
		std::string mainString = (*it).getListedIn().value();

		//test if mainString has genre as a substring
		if (mainString.find(genre) == std::string::npos)
			continue;

		similarMovies.push_back((*it).getId());
		count++;
	}

	return similarMovies;
}

double Database::cosineSimilarity(const std::vector<int>& firstUserRatings, const std::vector<int>& secondUserRatings)
{
	// Compute the dot product
	int dotProduct = 0;
	for (int i = 0; i < firstUserRatings.size(); i++) {
		dotProduct += firstUserRatings[i] * secondUserRatings[i];
	}
	// Compute the magnitudes
	double magnitude1 = 0;
	for (int rating : firstUserRatings) {
		magnitude1 += rating * rating;
	}
	magnitude1 = sqrt(magnitude1);
	double magnitude2 = 0;
	for (int rating : secondUserRatings) {
		magnitude2 += rating * rating;
	}
	magnitude2 = sqrt(magnitude2);
	// Return the cosine similarity
	return dotProduct / (magnitude1 * magnitude2);
}
	


std::array<std::optional<std::string>, Database::k_movieTableSize> split(const std::string& str, const std::string& delim)
{
	std::array<std::optional<std::string>, Database::k_movieTableSize> result;
	size_t startIndex = 0;
	int pos = 0;
	for (size_t found = str.find(delim); found != std::string::npos; found = str.find(delim, startIndex))
	{
		std::string tmp(str.begin() + startIndex, str.begin() + found);
		
			result[pos] = tmp;
		

		startIndex = found + delim.size();
		pos++;
	}
	std::string tmp(str.begin() + startIndex, str.end());
	if (startIndex != str.size())
		result[pos] = tmp;
	else
		result[pos] = "";

	return result;
}


void Database::PopulateStorage(const std::string& dataFilePath)
{
	int k_maxInsertRangeSupports = 2730;

	/* Get the number of movies by the number of lines in the .csv file*/
	std::ifstream in(dataFilePath);
	std::string str;
	int numberOfMovies = std::count(std::istreambuf_iterator<char>(in),
		std::istreambuf_iterator<char>(), '\n') + 1;
	in.close(); 
	
	/*Insert the .csv in Database*/
	in.open(dataFilePath);
	std::string delim("|");
	std::vector<Movie> movies;
	int movieCounter = 0;
	while (movieCounter < numberOfMovies)
	{
		while (movies.size() < k_maxInsertRangeSupports && getline(in, str))
		{
			//Id, Type, Title, Director, Cast, Country, Date_added, Release_year, Rating, Duration, Listed_in, Description, Poster_url
			std::array<std::optional<std::string>, Database::k_movieTableSize> result = split(str, delim);
			const auto& [id, type, title, director, cast, country, dateAdded,
						releaseYear, rating, duration, listedIn, description, posterUrl] = result;
			// ^^unpacking the array

			int rYear;
			if (*releaseYear != "")
			{
				rYear = std::stoi(*result[7]);
			}
			else
				rYear = -1;

			movies.emplace_back(Movie{ -1, *type, *title, *director, *cast, *country, *dateAdded,
				rYear, *rating, *duration, *listedIn, *description, *posterUrl });

			movieCounter++;
		}
		m_storage->insert_range(movies.begin(), movies.end());
		movies.clear();
	}
}
