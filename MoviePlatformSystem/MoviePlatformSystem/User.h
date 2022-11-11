#pragma once
#include <string>
#include <optional>

class User
{

private:
	int m_id; // PK
	std::string m_username;
	std::string m_password;
	int m_userInfoId; // FK
	std::optional<std::string> m_userPreferencesId; // FK
	std::optional<std::string> m_watchedId; // FK
	std::optional<std::string> m_wishlistId; // FK



public:
	User(); // no parameters constr.
	User(int id, std::string username, std::string password, int userInfoId, std::optional<std::string> userPreferencesId, std::optional<std::string> watchedId,
		std::optional<std::string> wishlistId);
	~User();

	//setters
	void setId(const int& id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setUserInfoId(const int& userInfoId);
	void setUserPreferencesId(const std::optional<std::string>& userPreferencesId);
	void setWatchedId(const std::optional<std::string>& watchedId);
	void setWishlistId(const std::optional<std::string>& wishlistId);


	//getters
	int getId() const;
	std::string getUsername() const;
	std::string getPassword() const;
	int getUserInfoId() const;
	std::optional<std::string> getUserPreferencesId() const;
	std::optional<std::string> getWatchedId() const;
	std::optional<std::string> getWishlistId() const;


};

