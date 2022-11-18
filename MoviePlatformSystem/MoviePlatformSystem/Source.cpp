#define SQLITE_ORM_OPTIONAL_SUPPORTED
#define SQLITE_ORM_OMITS_CODECVT

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



int main(int, char**)
{
	namespace sql = sqlite_orm;

	//auto platformDatabase = sql::make_storage(
	//	"moviePlatform.sqlite",
	//	sql::make_table
	//	(
	//		"movies",
	//		sql::make_column
	//		(
	//			"show_id",
	//			&Movie::getId,
	//			&Movie::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"type",
	//			&Movie::getType,
	//			&Movie::setType
	//		),
	//		sql::make_column
	//		(
	//			"title",
	//			&Movie::getTitle,
	//			&Movie::setTitle
	//		),
	//		sql::make_column
	//		(
	//			"director",
	//			&Movie::getDirector,
	//			&Movie::setDirector
	//		),
	//		sql::make_column
	//		(
	//			"cast",
	//			&Movie::getCast,
	//			&Movie::setCast
	//		),
	//		sql::make_column
	//		(
	//			"country",
	//			&Movie::getCountry,
	//			&Movie::setCountry
	//		),
	//		sql::make_column
	//		(
	//			"date_added",
	//			&Movie::getDateAdded,
	//			&Movie::setDateAdded
	//		),
	//		sql::make_column
	//		(
	//			"release_year",
	//			&Movie::getReleaseYear,
	//			&Movie::setReleaseYear
	//		),
	//		sql::make_column
	//		(
	//			"rating",
	//			&Movie::getRating,
	//			&Movie::setRating
	//		),
	//		sql::make_column
	//		(
	//			"duration",
	//			&Movie::getDuration,
	//			&Movie::setDuration
	//		),
	//		sql::make_column
	//		(
	//			"listed_in",
	//			&Movie::getListedIn,
	//			&Movie::setListedIn
	//		),
	//		sql::make_column
	//		(
	//			"description",
	//			&Movie::getDescription,
	//			&Movie::setDescription
	//		)
	//	),
	//	sql::make_table
	//	(
	//		"users",
	//		sql::make_column
	//		(
	//			"user_id",
	//			&User::getId,
	//			&User::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"username",
	//			&User::getUsername,
	//			&User::setUsername
	//		),
	//		sql::make_column
	//		(
	//			"password",
	//			&User::getPassword,
	//			&User::setPassword
	//		),
	//		sql::make_column(
	//			"user_info_id", // fk
	//			&User::getUserInfoId,
	//			&User::setUserInfoId
	//		),
	//		sql::make_column
	//		(
	//			"user_preferences_id", // fk
	//			&User::getUserPreferencesId,
	//			&User::setUserPreferencesId
	//		),
	//		sql::make_column
	//		(
	//			"user_watched_id", // fk
	//			&User::getWatchedId,
	//			&User::setWatchedId

	//		),
	//		sql::make_column
	//		(
	//			"user_wishlist_id", // fk
	//			&User::getWishlistId,
	//			&User::setWishlistId

	//		),
	//		sql::foreign_key(&User::setUserPreferencesId).references(&UserPreferences::setId) // have to.. 
	//																		   // ..figure it out why it's not working
	//	),// ^^ to add the FK
	//	sql::make_table
	//	(
	//		"user_preferences",
	//		sql::make_column
	//		(
	//			"id",
	//			&UserPreferences::getId,
	//			&UserPreferences::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"user_id", // fk
	//			&UserPreferences::getUserId,
	//			&UserPreferences::setUserId
	//		),

	//		sql::make_column
	//		(
	//			"show_id", // fk
	//			&UserPreferences::getShowId,
	//			&UserPreferences::setShowId
	//		)
	//	),
	//	sql::make_table
	//	(
	//		"user_info",
	//		sql::make_column
	//		(
	//			"id",
	//			&UserInfo::getId,
	//			&UserInfo::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"user_id", // fk
	//			&UserInfo::getUserId,
	//			&UserInfo::setUserId
	//		),

	//		sql::make_column
	//		(
	//			"fullname",
	//			&UserInfo::getFullName,
	//			&UserInfo::setFullName
	//		),
	//		sql::make_column
	//		(
	//			"age",
	//			&UserInfo::getAge,
	//			&UserInfo::setAge
	//		)
	//	),
	//	sql::make_table
	//	(
	//		"user_watched",
	//		sql::make_column
	//		(
	//			"id",
	//			&UserWatched::getId,
	//			&UserWatched::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"user_id", // fk
	//			&UserWatched::getUserId,
	//			&UserWatched::setUserId
	//		),
	//		sql::make_column
	//		(
	//			"show_id", // fk
	//			&UserWatched::getShowId,
	//			&UserWatched::setShowId
	//		)
	//	),
	//	sql::make_table
	//	(
	//		"user_wishlist",
	//		sql::make_column
	//		(
	//			"id",
	//			&UserWishlist::getId,
	//			&UserWishlist::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"user_id", // fk
	//			&UserWishlist::getUserId,
	//			&UserWishlist::setUserId
	//		),
	//		sql::make_column
	//		(
	//			"show_id", // fk
	//			&UserWishlist::getShowId,
	//			&UserWishlist::setShowId
	//		)
	//	),
	//	sql::make_table
	//	(
	//		"rating",
	//		sql::make_column
	//		(
	//			"id",
	//			&Rating::getId,
	//			&Rating::setId,
	//			sql::primary_key()
	//		),
	//		sql::make_column
	//		(
	//			"user_id", // fk
	//			&Rating::getUserId,
	//			&Rating::setUserId
	//		),
	//		sql::make_column
	//		(
	//			"show_id", // fk
	//			&Rating::getShowId,
	//			&Rating::setShowId
	//		),
	//		sql::make_column
	//		(
	//			"rating", // fk
	//			&Rating::getRating,
	//			&Rating::setRating
	//		)
	//	)
	//);

	//// TO ADD THE FKEYS!
	//platformDatabase.sync_schema(true);

	//// testing..

	////PRINT MOVIE DATA

	////display no. of movies in .prodb
	//std::ofstream file("movies.prodb");
	//auto allMovies = platformDatabase.get_all<Movie>();
	//file << "allMovies (" << allMovies.size() << "):" << std::endl;

	////display all movies in .prodb
	//for (auto& movie : platformDatabase.iterate<Movie>()) {
	//	file << platformDatabase.dump(movie) << std::endl;
	//}

	////USER TABLE CRUD OPERATIONS

	////insert
	//platformDatabase.replace(User("1", "user1Name", "password1","1", "1", "1", "1"));
	//platformDatabase.replace(User("2", "user2Name", "password2", "2", "2", "2", "2"));
	//platformDatabase.replace(User("3", "user3Name", "password3", "3", "3", "3", "3"));
	////delete
	//platformDatabase.remove<User>("1");

	////update
	//auto userId1 = platformDatabase.get<User>("2");
	//userId1.setId("1");
	//platformDatabase.update(userId1);

	////display
	//for (auto& user : platformDatabase.iterate<User>()) {
	//	std::cout << platformDatabase.dump(user) << std::endl;
	//}

	//std::cout << std::endl;

	////USER INFO TABLE CRUD OPERATIONS

	////insert
	//platformDatabase.replace(UserInfo("1", "1", "fullName1", "age1"));
	//platformDatabase.replace(UserInfo("2", "2", "fullName2", "age2"));
	//platformDatabase.replace(UserInfo("3", "3", "fullName3", "age3"));

	////delete
	//platformDatabase.remove<UserInfo>("1");

	////update
	//auto userInfo1 = platformDatabase.get<UserInfo>("2");
	//userInfo1.setId("1");
	//platformDatabase.update(userInfo1);

	////display
	//for (auto& userInfo : platformDatabase.iterate<UserInfo>()) {
	//	std::cout << platformDatabase.dump(userInfo) << std::endl;
	//}

	//std::cout << std::endl;

	////USER WATCHED TABLE CRUD OPERATIONS

	////insert
	//platformDatabase.replace(UserWatched("1", "1", "1"));
	//platformDatabase.replace(UserWatched("2", "2", "2"));
	//platformDatabase.replace(UserWatched("3", "3", "3"));

	////delete
	//platformDatabase.remove<UserWatched>("1");

	////update
	//auto userWatched1 = platformDatabase.get<UserWatched>("2");
	//userWatched1.setId("1");
	//platformDatabase.update(userWatched1);

	////display
	//for (auto& userWatched : platformDatabase.iterate<UserWatched>()) {
	//	std::cout << platformDatabase.dump(userWatched) << std::endl;
	//}


	////WISHLIST TABLE CRUD OPERATIONS
	//// 
	////insert
	//platformDatabase.replace(UserWishlist("1", "1", "s1"));
	//platformDatabase.replace(UserWishlist("2", "1", "s2"));
	//platformDatabase.replace(UserWishlist("3", "1", "s3"));

	////delete
	//platformDatabase.remove<UserWishlist>("1");

	////update
	//auto user = platformDatabase.get<UserWishlist>("2");
	//user.setShowId("s4");
	//platformDatabase.update(user);

	////display
	//auto wishlist = platformDatabase.get_all<UserWishlist>();
	//std::cout << "Wishlist Size: (" << wishlist.size() << "):" << std::endl;
	//for (auto& movie : wishlist) {
	//	std::cout << platformDatabase.dump(movie) << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url : 'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
	//}

	////USER PREFERENCES TABLE CRUD OPERATIONS
	//// 
	////insert
	//platformDatabase.replace(UserPreferences("1", "1", "s1"));
	//platformDatabase.replace(UserPreferences("2", "1", "s2"));
	//platformDatabase.replace(UserPreferences("3", "1", "s3"));

	////delete
	//platformDatabase.remove<UserPreferences>("1");

	////update
	//auto user2 = platformDatabase.get<UserPreferences>("2");
	//user.setShowId("s4");
	//platformDatabase.update(user2);

	////display
	//auto preferences = platformDatabase.get_all<UserPreferences>();
	//std::cout << "User Preferences Size: (" << preferences.size() << "):" << std::endl;
	//for (auto& movie : preferences) {
	//	std::cout << platformDatabase.dump(movie) << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url : 'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
	//}

	////RATING TABLE CRUD OPERATIONS
	//// 
	////insert
	//platformDatabase.replace(Rating("1", "1", "s1", "10.00"));
	//platformDatabase.replace(Rating("2", "1", "s2", "9.01"));
	//platformDatabase.replace(Rating("3", "1", "s3", "8.05"));

	////delete
	//platformDatabase.remove<Rating>("1");

	////update
	//auto user3 = platformDatabase.get<Rating>("2");
	//user3.setShowId("s4");
	//platformDatabase.update(user3);

	////display
	//auto rating = platformDatabase.get_all<Rating>();
	//std::cout << "Rating Size: (" << rating.size() << "):" << std::endl;
	//for (auto& movie : rating) {
	//	std::cout << platformDatabase.dump(movie) << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url : 'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
	//}
}