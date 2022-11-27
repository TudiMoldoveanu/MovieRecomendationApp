#include "Database.h"

Database::Database()
{
	 m_storage = std::make_unique<Storage>(initStorage("moviePlatform.sqlite"));
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
	auto* instance = getInstance();
	instance->m_storage->sync_schema();
	return instance;
}