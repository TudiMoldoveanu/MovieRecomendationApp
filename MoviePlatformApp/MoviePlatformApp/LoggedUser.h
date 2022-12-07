#pragma once
#include "User.h"
#include <iostream>
class LoggedUser
{
private:
	 std::unique_ptr<User> m_user;

private:
	LoggedUser(User* user = nullptr);
	LoggedUser(const LoggedUser&) = delete;			// the object can't be copied
	void operator=(const LoggedUser&) = delete;
	~LoggedUser() = delete;						// the object can't be deleted

private:
	// instantiate the database
	static LoggedUser* getInstance(User* user = nullptr);

public:
	// sync the instantiated database and return a pointer to it
	static LoggedUser* login(User* user = nullptr);


	int getId();
};

