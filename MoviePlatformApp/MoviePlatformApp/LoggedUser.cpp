#include "LoggedUser.h"


LoggedUser::LoggedUser(User* user)
{
	m_user = std::make_unique<User>(*user);
}

LoggedUser* LoggedUser::getInstance(User* user)
{
	static LoggedUser* loggedUser;
	if (loggedUser == nullptr)
	{
		loggedUser = new LoggedUser(user);
	}
	return loggedUser;
}


LoggedUser* LoggedUser::login(User* user)
{
	return getInstance(user);
}

std::string LoggedUser::getUsername() const
{
	return m_user->getUsername();
}

std::string LoggedUser::getPassword() const
{
	return m_user->getPassword();
}

User LoggedUser::getUser() const
{
	return *m_user;
}

void LoggedUser::setId(const int& id)
{
	m_user->setId(id);
}

void LoggedUser::setUsername(const std::string& username)
{
	m_user->setUsername(username);
}

void LoggedUser::setPassword(const std::string& password)
{
	m_user->setPassword(password);
}

int LoggedUser::getId()
{
	return m_user->getId();
}
