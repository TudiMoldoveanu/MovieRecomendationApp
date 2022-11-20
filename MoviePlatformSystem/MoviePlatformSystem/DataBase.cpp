#include "Database.h"


Storage Database::getStorage()
{
	return m_storage;
}

void Database::insertIntoUser(const User& user)
{
	getStorage().insert(user);
}

void Database::deleteFromUser(const int& id)
{
	getStorage().remove<User>(id);
}

void Database::updateAUser(const int& id,const int& newId)
{
	auto user = getStorage().get<User>(id);
	user.setId(newId);
	getStorage().update(user);
}
