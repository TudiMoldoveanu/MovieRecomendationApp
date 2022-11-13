#include "User.h"

User::User()
{}

User::User(std::string id, std::string username, std::string password, std::string userInfoId,
	std::optional<std::string> userPreferencesId, std::optional<std::string> watchedId,std::optional<std::string> wishlistId)
	:m_id{ id }, m_username{ std::move(username) }, m_password{ std::move(password) }, m_userInfoId{ userInfoId }, m_userPreferencesId{ userPreferencesId }, m_watchedId{ std::move(watchedId) },
	m_wishlistId{ std::move(wishlistId) }
{}

User::~User()
{}

//setters
void User::setId(const std::string& id)
{
	m_id = id;
}

void User::setUsername(const std::string& username)
{
	m_username = std::move(username);
}

void User::setPassword(const std::string& password)
{
	m_password = std::move(password);
}

void User::setUserInfoId(const std::string& userInfoId)
{
	m_userInfoId = userInfoId;
}

void User::setUserPreferencesId(const std::optional<std::string>& userPreferencesId)
{
	m_userPreferencesId = userPreferencesId;
}

void User::setWatchedId(const std::optional<std::string>& watchedId)
{
	m_watchedId = std::move(watchedId);
}

void User::setWishlistId(const std::optional<std::string>& wishlistId)
{
	m_wishlistId = std::move(wishlistId);
}


//getters
std::string User::getId() const
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

std::string User::getUserInfoId() const
{
	return m_userInfoId;
}

std::optional<std::string> User::getUserPreferencesId() const
{
	return m_userPreferencesId;
}

std::optional<std::string> User::getWatchedId() const
{
	return m_watchedId;
}

std::optional<std::string> User::getWishlistId() const
{
	return m_wishlistId;
}


