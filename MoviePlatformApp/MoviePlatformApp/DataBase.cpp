#include "Database.h"

Database::Database()
{
	 m_storage = std::make_unique<Storage>(initStorage("moviePlatform.sqlite"));
//<<<<<<< Updated upstream
	 std::cout << "Database connected!" << std::endl;

	 this->m_storage->sync_schema();

	 auto initMoviesCount = this->m_storage->count<Movie>();
	 if (initMoviesCount == 0)
		 this->PopulateStorage("movies_dataset.csv");
//=======
	 std::cout << "Database connected!" << std::endl; 
//>>>>>>> Stashed changes
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
	auto* instance = getInstance();
	return instance;
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
	std::ifstream in(dataFilePath);

	std::string str;

	 std::string delim("|");
	std::vector<Movie> movies;

	while (getline(in, str))
	{
		//Id, Type, Title, Director, Cast, Country, Date_added, Release_year, Rating, Duration, Listed_in, Description, Poster_url
		std::array<std::optional<std::string>, Database::k_movieTableSize> result = split(str, delim);
		int releaseYear;
		if (*result[7] != "")
		{
			releaseYear = std::stoi(*result[7]);
		}
		else
			releaseYear = -1;
		movies.emplace_back(Movie{ -1, *result[1], *result[2], *result[3], *result[4], *result[5], *result[6], 
			releaseYear, *result[8], *result[9], *result[10], *result[11], *result[12] });
		m_storage->insert(Movie{ -1, *result[1], *result[2], *result[3], *result[4], *result[5], *result[6],
			releaseYear, *result[8], *result[9], *result[10], *result[11], *result[12] });
	}

//	m_storage->insert_range(movies.begin(), movies.end()); //-> fast but throwing runtime error, to be improved this way...
}
