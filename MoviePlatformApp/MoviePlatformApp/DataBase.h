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

	// template useful functions
	template <class T>
	auto getAll()
	{
		auto allRecords = m_storage->get_all<T>();
		return allRecords;
	}
	

	// template CRUD functions
	template <class T>
	void insert(const T& instance)
	{
		m_storage->insert(instance);
	}

	template <class T>
	void deleteId(const int& id)
	{
		m_storage->remove<T>(id);
	}
public:
	static const int k_movieTableSize = 13;
};





