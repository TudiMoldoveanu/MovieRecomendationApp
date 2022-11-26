#pragma once
#include <string>
class UserInfo
{
private:
	int m_userId;//fk
	std::string m_fullName;
	std::string m_age;

public:
	UserInfo();
	UserInfo(int userId, std::string fullName, std::string age);
	~UserInfo();


	void setUserId(int userId);
	void setFullName(std::string fullName);
	void setAge(std::string age);


	int getUserId() const;
	std::string getFullName() const;
	std::string getAge() const;
};

