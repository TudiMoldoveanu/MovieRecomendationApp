#pragma once
#include <string>

class User
{

private:
	int m_id; // PK
	std::string m_username;
	std::string m_password;
	int m_userInfoId; // FK
	int m_userPreferencesId; // FK
	std::string m_watchedId; // FK
	std::string m_wishlistId; // FK



public:
	User(); // no parameters constr.
	User(int id, std::string username, std::string password, int userInfoId, int userPreferencesId, std::string watchedId,
		std::string wishlistId);
	~User();

	//setters
	void setId(const int& id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setUserInfoId(const int& userInfoId);
	void setUserPreferencesId(const int& userPreferencesId);
	void setWatchedId(const std::string& watchedId);
	void setWishlistId(const std::string& wishlistId);


	//getters
	int getId() const;
	std::string getUsername() const;
	std::string getPassword() const;
	int getUserInfoId() const;
	int getUserPreferencesId() const;
	std::string getWatchedId() const;
	std::string getWishlistId() const;


};

