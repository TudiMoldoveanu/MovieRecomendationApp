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

int LoggedUser::getId()
{
	return m_user->getId();
}
