#include "UserInfo.h"

UserInfo::UserInfo()
{
}

UserInfo::UserInfo(int userId, std::string fullName, std::string age)
	: m_userId{ userId }, m_fullName{ fullName }, m_age{ age } {}

UserInfo::~UserInfo()
{
}



void UserInfo::setUserId(int userId)
{
	m_userId = std::move(userId);
}

void UserInfo::setFullName(std::string fullName)
{
	m_fullName = fullName;
}

void UserInfo::setAge(std::string age)
{
	m_age = age;
}


int UserInfo::getUserId() const
{
	return m_userId;
}

std::string UserInfo::getFullName() const
{
	return m_fullName;
}

std::string UserInfo::getAge() const
{
	return m_age;
}
