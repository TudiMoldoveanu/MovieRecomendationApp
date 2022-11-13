#pragma once
#include <string>
class UserInfo
{
private:
	std::string m_id;//pk
	std::string m_fullName;
	std::string m_age;

public:
	UserInfo();
	UserInfo(std::string id, std::string fullName, std::string age);
	~UserInfo();

	void setId(const std::string& id);
	void setFullName(const std::string& fullName);
	void setAge(const std::string& age);

	std::string getId()const;
	std::string getFullName()const;
	std::string getAge()const;
};

