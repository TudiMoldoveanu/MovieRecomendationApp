#pragma once
#include"dbEngine.cpp"
class Database //Singleton
{
private:
	std::unique_ptr<Storage> m_storage; 
	Database();
	Database(const Database&) = delete;			// the object can't be copied
	void operator=(const Database&) = delete;
	~Database() = delete;						// the object can't be deleted
	
public:

	// instantiate the database
	static Database* getInstance();
	// sync the instantiated database and return a pointer to it
	static Database* connect();
};





