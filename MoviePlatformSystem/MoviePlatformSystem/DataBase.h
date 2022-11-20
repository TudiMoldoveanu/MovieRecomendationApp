#pragma once
#include"dbEngine.cpp"
class Database
{
private:
	Storage m_storage = initStorage("moviePlatform.sqlite");

public:
	Storage getStorage();
	void insertIntoUser(const User& user);

};

