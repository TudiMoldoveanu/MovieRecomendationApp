/*Creating storage variable*/

#pragma once
#define SQLITE_ORM_OPTIONAL_SUPPORTED
#define SQLITE_ORM_OMITS_CODECVT
#include<string>
#include <fstream>
#include "sqlite_orm/sqlite_orm.h"
#include "iostream"
#include "Movie.h"
#include "User.h"
#include "UserInfo.h"
#include "UserPreferences.h"
#include "UserWishlist.h"
#include "UserWatched.h"
#include "Rating.h"

inline auto initStorage(const std::string& path)
{
	namespace sql = sqlite_orm;

	return sql::make_storage(
		path,
		sql::make_table
		(
			"movies",
			sql::make_column
			(
				"show_id",
				&Movie::getId,
				&Movie::setId,
				sql::autoincrement(),
				sql::primary_key()

			),
			sql::make_column
			(
				"type",
				&Movie::getType,
				&Movie::setType
			),
			sql::make_column
			(
				"title",
				&Movie::getTitle,
				&Movie::setTitle
			),
			sql::make_column
			(
				"director",
				&Movie::getDirector,
				&Movie::setDirector
			),
			sql::make_column
			(
				"cast",
				&Movie::getCast,
				&Movie::setCast
			),
			sql::make_column
			(
				"country",
				&Movie::getCountry,
				&Movie::setCountry
			),
			sql::make_column
			(
				"date_added",
				&Movie::getDateAdded,
				&Movie::setDateAdded
			),
			sql::make_column
			(
				"release_year",
				&Movie::getReleaseYear,
				&Movie::setReleaseYear
			),
			sql::make_column
			(
				"rating",
				&Movie::getRating,
				&Movie::setRating
			),
			sql::make_column
			(
				"duration",
				&Movie::getDuration,
				&Movie::setDuration
			),
			sql::make_column
			(
				"listed_in",
				&Movie::getListedIn,
				&Movie::setListedIn
			),
			sql::make_column
			(
				"description",
				&Movie::getDescription,
				&Movie::setDescription
			),
			sql::make_column
			(
				"poster_url",
				&Movie::getPosterUrl,
				&Movie::setPosterUrl
			)
		),
		sql::make_table
		(
			"users",
			sql::make_column
			(
				"user_id",
				&User::getId,
				&User::setId,
				sql::primary_key(),
				sql::autoincrement()
			),
			sql::make_column
			(
				"username",
				&User::getUsername,
				&User::setUsername
			),
			sql::make_column
			(
				"password",
				&User::getPassword,
				&User::setPassword
			)
		),
		sql::make_table
		(
			"user_preferences",
			sql::make_column
			(
				"user_id", // fk
				&UserPreferences::getUserId,
				&UserPreferences::setUserId
			),
			sql::make_column
			(
				"show_id", // fk
				&UserPreferences::getShowId,
				&UserPreferences::setShowId
			),
			sql::primary_key(&UserPreferences::setUserId, &UserPreferences::setShowId),
			sql::foreign_key(&UserPreferences::setUserId).references(&User::setId),
			sql::foreign_key(&UserPreferences::setShowId).references(&Movie::setId)
		),
		sql::make_table
		(
			"user_info",
			sql::make_column
			(
				"user_id", // fk
				&UserInfo::getUserId,
				&UserInfo::setUserId
			),

			sql::make_column
			(
				"fullname",
				&UserInfo::getFullName,
				&UserInfo::setFullName
			),
			sql::make_column
			(
				"age",
				&UserInfo::getAge,
				&UserInfo::setAge
			),
			sql::primary_key(&UserInfo::getUserId),
			sql::foreign_key(&UserInfo::setUserId).references(&User::setId)

		),
		sql::make_table
		(
			"user_watched",
			sql::make_column
			(
				"user_id", // fk
				&UserWatched::getUserId,
				&UserWatched::setUserId
			),
			sql::make_column
			(
				"show_id", // fk
				&UserWatched::getShowId,
				&UserWatched::setShowId
			),
			sql::primary_key(&UserWatched::setUserId, &UserWatched::setShowId),
			sql::foreign_key(&UserWatched::setUserId).references(&User::setId),
			sql::foreign_key(&UserWatched::setShowId).references(&Movie::setId)
		),
		sql::make_table
		(
			"user_wishlist",
			sql::make_column
			(
				"user_id", // fk
				&UserWishlist::getUserId,
				&UserWishlist::setUserId
			),
			sql::make_column
			(
				"show_id", // fk
				&UserWishlist::getShowId,
				&UserWishlist::setShowId
			),
			sql::primary_key(&UserWishlist::setUserId, &UserWishlist::setShowId),
			sql::foreign_key(&UserWishlist::setUserId).references(&User::setId),
			sql::foreign_key(&UserWishlist::setShowId).references(&Movie::setId)
		),
		sql::make_table
		(
			"rating",
			sql::make_column
			(
				"user_id", // fk
				&Rating::getUserId,
				&Rating::setUserId
			),
			sql::make_column
			(
				"show_id", // fk
				&Rating::getShowId,
				&Rating::setShowId
			),
			sql::make_column
			(
				"rating", // fk
				&Rating::getRating,
				&Rating::setRating
			),
			sql::primary_key(&Rating::setUserId, &Rating::setShowId),
			sql::foreign_key(&Rating::setUserId).references(&User::setId),
			sql::foreign_key(&Rating::setShowId).references(&Movie::setId)
		)
	);


}
using Storage = decltype(initStorage(""));