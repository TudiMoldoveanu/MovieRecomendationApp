#pragma once
#include"dbEngine.cpp"
class Database //Singleton
{
private:
	std::unique_ptr<Storage> m_storage; 

private:
	Database();
	Database(const Database&) = delete;			// the object can't be copied
	void operator=(const Database&) = delete;
	~Database() = delete;						// the object can't be deleted

private:
	// instantiate the database
	static Database* getInstance();
	void PopulateStorage(const std::string& dataFilePath);
	
public:
	// sync the instantiated database and return a pointer to it
	static Database* connect();
	bool isRegistered(const std::string& username);
	bool userAlreadyRated(const int& userId, const int& selectedMovieId);
	std::vector<int> getSimilarGenreAndRating(const Movie& movie);
	std::vector<int>getSimilarDirectorOrCast(const Movie& movie);
	// template useful functions
	template <class T>
	auto getAll()
	{
		auto allRecords = m_storage->get_all<T>();
		return allRecords;
	}

	template <class T>
	auto getSavedMovies(const int& loggedInUser)
	{
		std::vector<int> movieIds;
		auto allRecords = m_storage->get_all<T>();

		for (int i = 0; i < allRecords.size(); i++) {
			if (allRecords[i].getUserId() == loggedInUser) {
				movieIds.push_back(allRecords[i].getShowId());
			}
		}

		return movieIds;
	}

	template <class T>
	auto getById(const int& id)
	{
		return m_storage->get<T>(id);
	}

	template <class T>
	auto getById(const int& id1, const int& id2)
	{
		return m_storage->get<T>(id1, id2);
	}

	template <class T>
	auto dump(const T& instance)
	{
		std::cout<< m_storage->dump(instance);
	}
	
	// template CRUD functions
	template <class T>
	void insert(const T& instance)
	{
		m_storage->insert(instance);
	}

	template <class T>
	void replace(const T& instance)
	{
		m_storage->replace(instance);
	}


	template <class T>
	void deleteId(const int& id)
	{
		m_storage->remove<T>(id);
	}

	template <class T>
	void deleteId(const int& id1, const int& id2)
	{
		m_storage->remove<T>(id1, id2);
	}
public:
	static const int k_movieTableSize = 13;
};





