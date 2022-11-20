#include <fstream>
#include "dbEngine.cpp"


int main(int, char** argv)

{
	namespace sql = sqlite_orm;
	using Storage = decltype(initStorage(""));
	Storage platformDatabase = initStorage("moviePlatform.sqlite");
	platformDatabase.sync_schema(true);

	// testing..

	//PRINT MOVIE DATA

	//display no. of movies in .prodb
	std::ofstream file("movies.prodb");
	auto allMovies = platformDatabase.get_all<Movie>();
	file << "allMovies (" << allMovies.size() << "):" << std::endl;

	//display all movies in .prodb
	for (auto& movie : platformDatabase.iterate<Movie>()) {
		file << platformDatabase.dump(movie) << std::endl;
	}

	/*USER TABLE CRUD OPERATIONS*/

	// a little example of insert
	User user{ -1, "anamaria", "pass" }; // i think the id really doesn't matter bcs we have the autoincrement that starts from 1
	platformDatabase.insert(user);
	platformDatabase.replace(UserInfo({ 1, "Ana Maria Prodan", "32" }));

	// COMMENTED TESTS FROM PREVIOUS STORAGE ARE DOWN BELOW

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
	//
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

	//insert
	platformDatabase.replace(UserWatched(1, "s1"));
	platformDatabase.replace(UserWatched(1, "s2"));

	//delete
	platformDatabase.remove<UserWatched>(1, "s1");

	//update
	auto userWatched1 = platformDatabase.get<UserWatched>(1, "s2");
	userWatched1.setShowId("s3");
	platformDatabase.update(userWatched1);

	//display
	for (auto& userWatched : platformDatabase.iterate<UserWatched>()) {
		std::cout << platformDatabase.dump(userWatched) << std::endl;
	}

	//
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