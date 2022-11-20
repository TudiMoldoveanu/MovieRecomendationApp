#include "Database.h"


Storage Database::getStorage()
{
	return m_storage;
}

void Database::insertIntoUser(const User& user)
{
	getStorage().insert(user);
}