#pragma once
#include <string>


class User
{

private:
	int m_id; // PK
	std::string m_username;
	std::string m_password;

public:
	User(); // no parameters constr.

	User(int id, std::string username, std::string password);
	~User();

	//setters
	void setId(int id);
	void setUsername(std::string username);
	void setPassword(std::string password);

	//getters
	int getId() const;
	std::string getUsername() const;
	std::string getPassword() const;

};

