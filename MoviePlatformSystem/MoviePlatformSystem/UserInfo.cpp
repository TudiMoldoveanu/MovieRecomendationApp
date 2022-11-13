#include "UserInfo.h"

UserInfo::UserInfo()
{
}

UserInfo::UserInfo(std::string id, std::string fullName, std::string age)
	:m_id{ id }, m_fullName{ fullName }, m_age{ age } {}

UserInfo::~UserInfo()
{
}

void UserInfo::setId(const std::string& id)
{
	m_id = id;
}

void UserInfo::setFullName(const std::string& fullName)
{
	m_fullName = fullName;
}

void UserInfo::setAge(const std::string& age)
{
	m_age = age;
}

std::string UserInfo::getId() const
{
	return m_id;
}

std::string UserInfo::getFullName() const
{
	return m_fullName;
}

std::string UserInfo::getAge() const
{
	return m_age;
}
