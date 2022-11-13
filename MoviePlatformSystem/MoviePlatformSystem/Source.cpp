#define SQLITE_ORM_OPTIONAL_SUPPORTED
#define SQLITE_ORM_OMITS_CODECVT

#include "sqlite_orm/sqlite_orm.h"
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

    auto platformDatabase = sql::make_storage(
        "moviePlatform.sqlite",
        sql::make_table
        (
            "movies",
            sql::make_column
            (
                "show_id",
                &Movie::getId,
                &Movie::setId,
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
                sql::primary_key()
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
            ),
            sql::make_column(
                "user_info_id", // fk
                &User::getUserInfoId,
                &User::setUserInfoId
            ), 
            sql::make_column
            (
                "user_preferences_id", // fk
                &User::getUserPreferencesId,
                &User::setUserPreferencesId
            ),
            sql::make_column
            (
                "user_watched_id", // fk
                &User::getWatchedId,
                &User::setWatchedId
               
            ),
            sql::make_column
            (
                "user_wishlist_id", // fk
                &User::getWishlistId,
                &User::setWishlistId
               
            ),
            sql::foreign_key(&User::setUserPreferencesId).references(&UserPreferences::setId) // have to.. 
                                                                               // ..figure it out why it's not working
            ),// ^^ to add the FK
            sql::make_table
            (
                "user_preferences", 
                sql::make_column
                (
                    "id", 
                    &UserPreferences::getId,
                    &UserPreferences::setId,
                    sql::primary_key()
                    ),
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
                )
       ),
                sql::make_table
                (
                    "user_info",
                    sql::make_column
                    (
                        "id",
                        &UserInfo::getId,
                        &UserInfo::setId,
                        sql::primary_key()
                    ),
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
                    )
                ),
                sql::make_table
                (
                    "user_watched",
                    sql::make_column
                    (
                        "id",
                        &UserWatched::getId,
                        &UserWatched::setId,
                        sql::primary_key()
                    ),
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
                    )
                ),
                sql::make_table
                (
                    "user_wishlist",
                    sql::make_column
                    (
                        "id",
                        &UserWishlist::getId,
                        &UserWishlist::setId,
                        sql::primary_key()
                    ),
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
                    )
                ),
                sql::make_table
                (
                    "rating",
                    sql::make_column
                    (
                        "id",
                        &Rating::getId,
                        &Rating::setId,
                        sql::primary_key()
                    ),
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
                    )
                )
                    );

                    // TO ADD THE FKEYS!
    platformDatabase.sync_schema(true);

    // testing..

}