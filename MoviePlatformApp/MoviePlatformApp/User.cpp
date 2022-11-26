#include "User.h"

User::User()
{}



User::User(int id, std::string username, std::string password)
	:m_id{ id }, m_username{ std::move(username) }, m_password{ std::move(password) }
{}

User::~User()
{}

//setters
void User::setId(int id)
{
	m_id = id;
}

void User::setUsername(std::string username)
{
	m_username = std::move(username);
}

void User::setPassword(std::string password)
{
	m_password = std::move(password);
}




//getters
int User::getId() const
{
	return m_id;
}

std::string User::getUsername() const
{
	return m_username;
}

std::string User::getPassword() const
{
	return m_password;
}

