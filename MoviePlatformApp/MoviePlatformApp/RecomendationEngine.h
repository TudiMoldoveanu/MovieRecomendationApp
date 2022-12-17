#pragma once

#include "UserWatched.h"
#include"UserPreferences.h"
#include"DataBase.h"
#include"Movie.h"

class RecomendationEngine
{
private:

	UserPreferences m_userPref;
	int m_userId;

public:

	RecomendationEngine(int userId);

};

