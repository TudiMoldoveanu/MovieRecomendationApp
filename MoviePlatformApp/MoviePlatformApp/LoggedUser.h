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
	// instantiate the loggedUser
	static LoggedUser* getInstance(User* user = nullptr);

public:
	static LoggedUser* login(User* user = nullptr);

	// getters
	int getId();
	std::string getUsername() const;
	std::string getPassword() const;
	User getUser() const;

	//setters
	void setId(const int& id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
};

